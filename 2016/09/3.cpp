#include <iostream>
#include <vector>
using namespace std;
// #define DEBUG

const int maxn = 1005;
struct Role {
    int attack, health;
    Role() {}
    Role(int _attack, int _health)
        : attack(_attack)
        , health(_health) {}
};
vector<Role> role[2];

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    role[0].push_back(Role(0, 30));
    role[1].push_back(Role(0, 30));
    int n;
    scanf("%d", &n);
    char order[10];
    int pos1, pos2, attack, health, turn = 0;
    while (n--) {
        scanf("%s", order);
        if (order[0] == 's') {
            scanf("%d%d%d", &pos1, &attack, &health);
            role[turn].insert(role[turn].begin() + pos1, Role(attack, health));
        } else if (order[0] == 'a') {
            scanf("%d%d", &pos1, &pos2);
            role[turn][pos1].health -= role[1 - turn][pos2].attack;
            role[1 - turn][pos2].health -= role[turn][pos1].attack;
            if (role[turn][pos1].health <= 0)
                role[turn].erase(role[turn].begin() + pos1);
            //注意点：英雄死亡时不要删除，否则只有70分
            if (pos2 != 0 && role[1 - turn][pos2].health <= 0)
                role[1 - turn].erase(role[1 - turn].begin() + pos2);
        } else
            turn = 1 - turn;
    }
    if (role[0][0].health <= 0)
        printf("-1\n");
    else if (role[1][0].health <= 0)
        printf("1\n");
    else
        printf("0\n");
    for (int i = 0; i < 2; ++i) {
        printf("%d\n", role[i][0].health);
        printf("%d", role[i].size() - 1);
        for (int j = 1; j < role[i].size(); ++j) {
            printf(" %d", role[i][j].health);
        }
        puts("");
    }
    return 0;
}