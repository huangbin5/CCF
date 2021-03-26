#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
// #define DEBUG

vector<string> html;
map<string, string> val;
int m, n;

void handle(int x) {
    string line = html[x], key;
    int cur = 0, pre, post;
    while ((pre = line.find("{{", cur)) != -1) {
        cout << line.substr(cur, pre - cur);
        post = line.find("}}", cur);
        key = line.substr(pre + 3, post - pre - 4);
        if (val.count(key))
            cout << val[key];
        cur = post + 2;
    }
    if (cur != line.size())
        cout << line.substr(cur, line.size() - cur);
    cout << endl;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> m >> n;
    //注意要吃掉换行符
    getchar();
    string line;
    while (m--) {
        getline(cin, line);
        html.push_back(line);
    }
    string key;
    while (n--) {
        cin >> key;
        getline(cin, line);
        int len = line.size();
        //去掉前导空格和一对引号
        val[key] = line.substr(2, line.size() - 3);
    }
    for (int i = 0; i < html.size(); ++i) {
        handle(i);
    }
    return 0;
}