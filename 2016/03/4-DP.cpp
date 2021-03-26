#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 105;
const int direc[][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
int t1[maxn][maxn] = { 0 }, t2[maxn][maxn] = { 0 };
//时间维度要是300以上
bool dp[maxn][maxn][maxn * 3] = { 0 };
int n, m, d;

bool valid(int x, int y) {
    if (x >= 1 && x <= n && y >= 1 && y <= m)
        return true;
    return false;
}

bool safe(int x, int y, int t) {
    if (t < t1[x][y] || t > t2[x][y])
        return true;
    return false;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &d);
    int x, y, a, b;
    while (d--) {
        scanf("%d%d%d%d", &x, &y, &a, &b);
        t1[x][y] = a;
        t2[x][y] = b;
    }
    dp[1][1][0] = 1;
    int t = 0;
    while (++t)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (safe(i, j, t))
                    for (int k = 0; k < 4; ++k) {
                        int x = i + direc[k][0], y = j + direc[k][1];
                        if (valid(x, y) && dp[x][y][t - 1] == 1) {
                            dp[i][j][t] = 1;
                            if (i == n && j == m) {
                                printf("%d", t);
                                return 0;
                            }
                            break;
                        }
                    }
    return 0;
}