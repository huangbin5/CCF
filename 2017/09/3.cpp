#include <iostream>
#include <map>
#include <stack>
#include <string>
using namespace std;
// #define DEBUG

struct Node {
    // 0-字符串；1-对象
    int type;
    string str;
    map<string, Node>* obj;
    Node() {}
    Node(int _type)
        : type(_type) {}
};
map<string, Node> obj;
string s = "";

//去除字符串中的所有空格
void trim(string& x) {
    int pos = 0;
    for (;;) {
        pos = x.find(' ', pos);
        if (pos == -1)
            break;
        x.erase(pos, 1);
    }
}

//将转义字符取出
string& handleWord(string& w) {
    int pos = 0;
    for (;;) {
        pos = w.find('\\', pos);
        if (pos == -1)
            break;
        w.erase(pos, 1);
        ++pos;
    }
    return w;
}

//将字符串处理成对象
void handleObject() {
    //存放对象的层次关系
    stack<map<string, Node>*> st;
    st.push(&obj);
    //保存当前对象的指针
    map<string, Node>* p = st.top();
    //{"first":{"second":"third","second":"third"},"second":"third"}
    int pos1 = 0, pos2, pos;
    string key, value;
    for (;;) {
        pos2 = s.find(':', pos1);
        if (pos2 == -1)
            break;
        key = s.substr(pos1 + 2, pos2 - pos1 - 3);
        handleWord(key);
        if (s[pos2 + 1] == '"') {
            //值是字符串
            (*p)[key] = Node(0);
            pos = pos1 = s.find(',', pos2);
            //到了对象的末尾
            if (pos1 == -1)
                pos = s.size();
            while (s[pos - 1] == '}')
                --pos;
            value = s.substr(pos2 + 2, pos - pos2 - 3);
            (*p)[key].str = handleWord(value);
            if (s[pos] == '}' && st.size() > 1) {
                st.pop();
                p = st.top();
            }
        } else {
            //值是对象
            (*p)[key] = Node(1);
            (*p)[key].obj = new map<string, Node>;
            st.push((*p)[key].obj);
            p = st.top();
            pos1 = pos2 + 1;
        }
    }
}

//打印对象
void printObject(map<string, Node>& mp) {
    cout << "{" << endl;
    for (map<string, Node>::iterator it = mp.begin(); it != mp.end(); ++it) {
        if (it->second.type == 0) {
            cout << it->first << ":" << it->second.str << endl;
        } else {
            cout << it->first << ":";
            printObject(*it->second.obj);
        }
    }
    cout << "}" << endl;
}

void getAns(string& q) {
    map<string, Node>* p = &obj;
    string key;
    int pos1 = 0, pos2;
    for (;;) {
        pos2 = q.find('.', pos1);
        if (pos2 == -1)
            break;
        key = q.substr(pos1, pos2 - pos1);
        if (p->count(key) == 0 || (*p)[key].type == 0) {
            cout << "NOTEXIST" << endl;
            return;
        }
        p = (*p)[key].obj;
        pos1 = pos2 + 1;
    }
    key = q.substr(pos1, q.size() - pos1);
    if (p->count(key) == 0)
        cout << "NOTEXIST" << endl;
    else if ((*p)[key].type == 1)
        cout << "OBJECT" << endl;
    else
        cout << "STRING " << (*p)[key].str << endl;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    getchar();
    string line;
    while (n--) {
        getline(cin, line);
        s += line;
    }
    trim(s);
    handleObject();
    // printObject(obj);
    while (m--) {
        getline(cin, line);
        getAns(line);
    }
    return 0;
}