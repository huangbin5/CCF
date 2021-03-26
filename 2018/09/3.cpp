#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
// #define DEBUG

struct Ele {
    string name, id;
    int level, line;
    Ele* father;
    vector<Ele*>* son;
    Ele() {}
    Ele(string _name, string _id, int _level, int _line, Ele* _father = NULL)
        : name(_name)
        , id(_id)
        , level(_level)
        , line(_line) {
        son = new vector<Ele*>;
    }
} * root;
int n, m;
vector<int> ans;
vector<string> tag;
stack<Ele*> pTag;

void getInput() {
    Ele* p;
    string name, id;
    for (int i = 1; i <= n; ++i) {
        //清空id
        id = "";
        getline(cin, name);
        //找到id的位置
        int pos = name.find(' ');
        if (pos != -1) {
            id = name.substr(pos + 1);
            name = name.substr(0, pos);
        }
        /**
         * 一开始漏了，调试了很久，回去再看题才想起
         */
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        //计算层级
        pos = name.find_first_not_of('.');
        //根节点
        if (pos == 0) {
            p = root = new Ele(name, id, 0, i);
        } else {
            name = name.substr(pos);
            int level = pos / 2;
            //找到上级
            if (level <= p->level)
                while (level <= p->level)
                    p = p->father;
            //往下深入一级
            else if (level > p->level + 1)
                p = p->son->back();
            p->son->push_back(new Ele(name, id, level, i));
            //维护父子关系
            p->son->back()->father = p;
        }
    }
}

bool dfsId(Ele* p, string id) {
    if (p->id == id) {
        cout << 1 << " " << p->line << endl;
        return true;
    }
    for (int i = 0; i < p->son->size(); ++i) {
        if (dfsId((*(p->son))[i], id))
            return true;
    }
    return false;
}

void dfsName(Ele* p, string name) {
    if (p->name == name)
        ans.push_back(p->line);
    for (int i = 0; i < p->son->size(); ++i)
        dfsName((*(p->son))[i], name);
}

void dfsSon(Ele* p, int idx) {
    if (p->name == tag[idx] || p->id == tag[idx]) {
        if (idx == tag.size() - 1)
            //找到一个结果
            ans.push_back(p->line);
        else {
            //继续检查下一个子标签
            ++idx;
            pTag.push(p);
        }
    }
    for (int i = 0; i < p->son->size(); ++i)
        dfsSon((*(p->son))[i], idx);
    if (!pTag.empty() && pTag.top() == p) {
        pTag.pop();
        --idx;
    }
}

void printAns() {
    if (ans.empty())
        cout << 0 << endl;
    else {
        cout << ans.size();
        for (int i = 0; i < ans.size(); ++i)
            cout << " " << ans[i];
        cout << endl;
    }
}

void select(string name) {
    tag.clear();
    ans.clear();
    int pos1 = 0, pos2 = name.find(' ');
    if (pos2 == -1) {
        if (name[0] == '#') {
            // id选择器
            if (!dfsId(root, name))
                cout << 0 << endl;
        } else {
            //标签选择器
            transform(name.begin(), name.end(), name.begin(), ::tolower);
            dfsName(root, name);
            printAns();
        }
    } else {
        //后代选择器
        do {
            string tmp = name.substr(pos1, pos2 - pos1);
            if (tmp[0] != '#')
                transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
            tag.push_back(tmp);
            pos1 = pos2 + 1;
            pos2 = name.find(' ', pos1);
        } while (pos2 != -1);
        tag.push_back(name.substr(pos1));
        dfsSon(root, 0);
        printAns();
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> m;
    getchar();
    getInput();
    string name;
    while (m--) {
        getline(cin, name);
        select(name);
    }
    return 0;
}