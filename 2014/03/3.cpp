#include <iostream>
#include <map>
#include <set>
#include <sstream>
using namespace std;
// #define DEBUG

//选项是否有参数，以及参数是什么
struct Option {
    bool hasArg;
    string arg;
    Option() {}
    Option(bool _hasArg)
        : hasArg(_hasArg) {}
};
set<char> st;
map<char, Option> mp;
string str;
int n;

bool legal(string s) {
    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c != '-' && !(c >= '0' && c <= '9') && !(c >= 'a' && c <= 'z'))
            return false;
    }
    return true;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> str;
    for (int i = 0; i < str.size(); ++i) {
        if (i < str.size() - 1 && str[i + 1] == ':') {
            mp[str[i]] = Option(true);
            ++i;
        } else {
            mp[str[i]] = Option(false);
        }
    }
    cin >> n;
    /**
     * 读取换行符，否则第一个getline读到的是换行符
     */
    getchar();
    string line;
    // curOp保存当前选项
    char curOp;
    for (int i = 1; i <= n; ++i) {
        st.clear();
        //读取一行
        getline(cin, line);
        stringstream ss(line);
        //读取命令行工具
        ss >> str;
        while (ss >> str) {
            //非法选项
            if (str.size() != 2 || str[0] != '-' || mp.count(str[1]) == 0) {
                break;
            }
            curOp = str[1];
            //带参数
            if (mp[curOp].hasArg) {
                if (ss >> str && legal(str)) {
                    mp[curOp].arg = str;
                    st.insert(curOp);
                } else
                    break;
            } else {
                st.insert(curOp);
            }
        }
        cout << "Case " << i << ":";
        if (st.empty())
            //没有任何选项也要输出一个空格
            cout << " ";
        else
            for (set<char>::iterator it = st.begin(); it != st.end(); ++it) {
                cout << " -" << *it;
                if (mp[*it].hasArg)
                    cout << " " << mp[*it].arg;
            }
        cout << endl;
    }
    return 0;
}