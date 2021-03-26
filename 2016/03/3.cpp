#include <iostream>
#include <string>
#include <vector>
using namespace std;
// #define DEBUG

int n;
vector<string> cur, ans;

void handle(string& s, vector<string>& v) {
    v.clear();
    string name;
    if (s.empty())
        //当前目录
        v = cur;
    else {
        //相对路径
        if (s[0] != '/')
            v = cur;
        int left = 0, right = 0;
        while (left < s.size() && right < s.size()) {
            // left-当前第一个非'/'的位置
            left = right;
            while (left < s.size() && s[left] == '/')
                ++left;
            // right-当前第一个'/'的位置
            right = left;
            while (right < s.size() && s[right] != '/')
                ++right;
            //不以'/'结束才要处理
            if (left < right) {
                name = s.substr(left, right - left);
                if (name != "." && name != "..")
                    v.push_back(name);
                if (name == ".." && !v.empty())
                    v.pop_back();
            }
        }
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    getchar();
    string line;
    getline(cin, line);
    handle(line, cur);
    while (n--) {
        getline(cin, line);
        handle(line, ans);
        if (ans.empty())
            cout << "/";
        else
            for (int i = 0; i < ans.size(); ++i)
                cout << "/" << ans[i];
        cout << endl;
    }
    return 0;
}