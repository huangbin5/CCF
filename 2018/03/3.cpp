#include <cctype>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// #define DEBUG

enum Type { NORMAL, INT, STR, PATH };
struct Seg {
    // 0-正常；1-int；2-str；3-path
    int flag;
    // flag = 0时生效
    string name;
    Seg(int _flag, string _name = "")
        : flag(_flag)
        , name(_name) {}
};
struct Rule {
    string name;
    vector<Seg> path;
    bool tail;
    Rule(string _name)
        : name(_name) {
        tail = 1;
    }
};
vector<Rule> rule;
int n, m;

void handleUrl(string& url) {
    if (url.back() != '/') {
        url.push_back('/');
        rule.back().tail = 0;
    }
    vector<Seg>& path = rule.back().path;
    int pos1 = 1, pos2;
    string tmp;
    for (;;) {
        pos2 = url.find('/', pos1);
        if (pos2 == -1)
            break;
        tmp = url.substr(pos1, pos2 - pos1);
        if (tmp == "<int>")
            path.push_back(Seg(INT));
        else if (tmp == "<str>")
            path.push_back(Seg(STR));
        else if (tmp == "<path>")
            path.push_back(Seg(PATH));
        else
            path.push_back(Seg(NORMAL, tmp));
        pos1 = pos2 + 1;
    }
}

void getAns(string& url) {
    string backup = url;
    if (url.back() != '/')
        url.push_back('/');
    for (int i = 0; i < rule.size(); ++i) {
        //存放参数
        vector<string> args;
        vector<Seg>& path = rule[i].path;
        /**
         * 末尾是否有'/'也要匹配，注意判空
         */
        if (((rule[i].tail) ^ (backup.back() == '/')) && !path.empty() && path.back().flag != PATH)
            continue;
        int pos1 = 1, pos2, j;
        for (j = 0; j < path.size(); ++j) {
            Seg& seg = path[j];
            //路径，则直接匹配
            if (seg.flag == PATH) {
                args.push_back(backup.substr(pos1));
                //为了统一下面的匹配成功的判断
                pos1 = url.size();
                j = path.size();
                break;
            }
            pos2 = url.find('/', pos1);
            // url匹配结束了
            if (pos2 == -1)
                break;
            string tmp = url.substr(pos1, pos2 - pos1);
            pos1 = pos2 + 1;
            if (seg.flag == NORMAL && seg.name == tmp)
                continue;
            if (seg.flag == INT) {
                bool flag = true;
                for (int k = 0; k < tmp.size(); ++k)
                    if (!isdigit(tmp[k])) {
                        flag = false;
                        break;
                    }
                if (flag) {
                    int pos = 0;
                    while (pos < tmp.size() - 1 && tmp[pos] == '0')
                        ++pos;
                    args.push_back(tmp.substr(pos));
                    continue;
                }
            }
            if (seg.flag == STR) {
                args.push_back(tmp);
                continue;
            }
            break;
        }
        //匹配成功
        if (j == path.size() && pos1 == url.size()) {
            cout << rule[i].name;
            for (j = 0; j < args.size(); ++j)
                cout << " " << args[j];
            cout << endl;
            return;
        }
    }
    cout << "404" << endl;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> m;
    string url, name;
    while (n--) {
        cin >> url >> name;
        rule.push_back(Rule(name));
        handleUrl(url);
    }
    while (m--) {
        cin >> url;
        getAns(url);
    }
    return 0;
}