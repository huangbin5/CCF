#include <cstdio>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
typedef long long ll;

const int maxm = 55;
struct Commodity {
    int type, id, score;
    Commodity(int _type, int _id, int _score) : type(_type), id(_id), score(_score) {}
    bool operator<(const Commodity& a) const {
        if (score != a.score)
            return score > a.score;
        if (type != a.type)
            return type < a.type;
        return id < a.id;
    }
};

inline int read() {
    int x = 0, sign = 1;
    char c = getchar();
    // 符号
    for (; c < '0' || '9' < c; c = getchar())
        if (c == '-')
            sign = -1;
    // 多位数字
    for (; '0' <= c && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    return x * sign;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    set<Commodity> commodities;
    vector<Commodity> ans[maxm];
    unordered_map<int, int> map[maxm];
    int m, n;
    m = read(), n = read();
    int id, score;
    for (int i = 0; i < n; ++i) {
        id = read(), score = read();
        for (int j = 0; j < m; ++j) {
            commodities.insert(Commodity(j, id, score));
            map[j][id] = score;
        }
    }
    int opNum, op, type, k, ki[maxm];
    opNum = read();
    while (opNum--) {
        op = read();
        if (op == 3) {
            // 查询
            k = read();
            for (int i = 0; i < m; ++i) {
                ki[i] = read();
                ans[i].clear();
            }
            for (auto commodity : commodities)
                if (ans[commodity.type].size() < ki[commodity.type]) {
                    ans[commodity.type].push_back(commodity);
                    if (!--k)
                        break;
                }
            for (int i = 0; i < m; ++i)
                if (ans[i].size() == 0)
                    printf("-1\n");
                else {
                    for (auto commodity : ans[i])
                        printf("%d ", commodity.id);
                    putchar('\n');
                }
        } else {
            type = read(), id = read();
            if (op == 1) {
                // 添加
                score = read();
                commodities.insert(Commodity(type, id, score));
                map[type][id] = score;
            } else
                // 删除
                commodities.erase(Commodity(type, id, map[type][id]));
        }
    }
    return 0;
}