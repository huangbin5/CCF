#include <iostream>
#include <map>
#include <string>
using namespace std;
// #define DEBUG

map<string, map<string, int>> role, user;
int p, r, u, q;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    //权限不需要处理
    cin >> p;
    string privName;
    int level;
    while (p--)
        cin >> privName;
    //角色
    cin >> r;
    string roleName;
    int num;
    while (r--) {
        cin >> roleName >> num;
        map<string, int>& mp = role[roleName];
        //角色的权限
        while (num--) {
            cin >> privName;
            int pos = privName.find(':');
            if (pos != -1) {
                string priv = privName.substr(0, pos);
                level = privName[pos + 1] - '0';
                //之前已经存在并且等级更高，则不处理
                if (mp.count(priv) == 0 || mp[priv] < level)
                    mp[priv] = level;
            } else
                //无等级的权限等级设为-1
                mp[privName] = -1;
        }
    }
    //用户
    cin >> u;
    string userName;
    while (u--) {
        cin >> userName >> num;
        map<string, int>& mp = user[userName];
        //用户的角色
        while (num--) {
            cin >> roleName;
            //悉数将角色的权限加到用户里面
            for (map<string, int>::iterator it = role[roleName].begin(); it != role[roleName].end(); ++it) {
                privName = it->first;
                level = it->second;
                if (mp.count(privName) == 0 || mp[privName] < level)
                    mp[privName] = level;
            }
        }
    }
    //查询
    cin >> q;
    while (q--) {
        cin >> userName >> privName;
        map<string, int>& mp = user[userName];
        int pos = privName.find(':');
        if (pos != -1) {
            //带等级查询
            string priv = privName.substr(0, pos);
            level = privName[pos + 1] - '0';
            if (mp.count(priv) == 0 || mp[priv] < level)
                printf("false\n");
            else
                printf("true\n");
        } else {
            //不带等级查询
            if (mp.count(privName) == 0)
                printf("false\n");
            else if (mp[privName] == -1)
                printf("true\n");
            else
                printf("%d\n", mp[privName]);
        }
    }
    return 0;
}