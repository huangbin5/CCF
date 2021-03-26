#include <iostream>
#include <string>
using namespace std;
// #define DEBUG

string& handle(string& s) {
    int pos = 0;
    //强调
    while (pos < s.size()) {
        pos = s.find('_', pos);
        if (pos == -1)
            break;
        s.replace(pos, 1, "<em>");
        pos = s.find('_', pos);
        s.replace(pos, 1, "</em>");
    }
    int pos1 = 0, pos2, pos3;
    //超链接
    while (pos1 < s.size()) {
        pos1 = s.find('[', pos1);
        if (pos1 == -1)
            break;
        pos2 = s.find(']', pos1);
        pos3 = s.find(')', pos1);
        s.replace(pos1, pos3 - pos1 + 1,
            "<a href=\"" + s.substr(pos2 + 2, pos3 - pos2 - 2) + "\">" + s.substr(pos1 + 1, pos2 - pos1 - 1) + "</a>");
    }
    return s;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    string line;
    bool listFlag = false, textFlag = false;
    while (getline(cin, line)) {
        //正文结尾
        if (line.empty() || line[0] == '#' || line[0] == '*') {
            if (textFlag) {
                cout << "</p>" << endl;
                textFlag = false;
            }
        }
        //列表结尾
        if (line.empty() || line[0] != '*') {
            if (listFlag) {
                cout << "</ul>" << endl;
                listFlag = false;
            }
        }
        if (line.empty())
            continue;
        if (line[0] == '*') {
            //列表
            if (!listFlag) {
                listFlag = true;
                cout << "<ul>" << endl;
            }
            int first = 1;
            while (line[first] == ' ')
                ++first;
            line = line.substr(first);
            cout << "<li>" << handle(line) << "</li>" << endl;
        } else if (line[0] == '#') {
            //标题
            int cnt = 0;
            while (line[cnt] == '#')
                ++cnt;
            int first = cnt;
            while (line[first] == ' ')
                ++first;
            line = line.substr(first);
            cout << "<h" << cnt << ">" << handle(line) << "</h" << cnt << ">" << endl;
        } else {
            //正文
            if (textFlag)
                cout << endl;
            else {
                textFlag = true;
                cout << "<p>";
            }
            cout << handle(line);
        }
    }
    //结尾要判断是否是列表或正文
    if (textFlag)
        cout << "</p>";
    if (listFlag)
        cout << "</ul>";
    return 0;
}