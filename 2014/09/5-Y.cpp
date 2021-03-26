/**
 * https://blog.csdn.net/vcvycy/article/details/78243162
 * 插头DP
 * DP分类
 */
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
#define DEBUG
#define MOD 1000000007
#define MM 7
int a[1 << MM][1 << MM];
long long n;
int m;
#define VACANT(S, u) (u >= 0 && u < m && ((S & (1 << u)) == 0))
int SETADD(int S, int u1, int u2 = -1) {
    S |= 1 << u1;
    if (u2 != -1)
        S |= 1 << u2;
    return S;
}
int c[1 << MM][1 << MM];
void mat_mul(int a[][1 << MM], int b[][1 << MM], int sz = 1 << m) {
    memset(c, 0, sizeof(c));
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            for (int k = 0; k < sz; k++) {
                c[i][j] = (c[i][j] + 1ll * a[i][k] * b[k][j]) % MOD;
            }
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            a[i][j] = c[i][j];
}
void search(int originS, int S1, int S2 = 0) {
    // printf("S1=%d,S2=%d\n",S1,S2);
    if (S1 == (1 << m) - 1) {
        // printf("%d->%d +1\n",originS,S2);
        a[originS][S2]++;
        return;
    }
    for (int i = 0; i < m; i++) //找到第一个没被占用的格子，然后继续搜索
        if (VACANT(S1, i)) { //格子i没有被占用
            // ↙是缺的
            if (VACANT(S1, i + 1) && VACANT(S2, i + 1)) {
                search(originS, SETADD(S1, i, i + 1), SETADD(S2, i + 1));
            }
            // ↘是缺的
            if (VACANT(S1, i + 1) && VACANT(S2, i))
                search(originS, SETADD(S1, i, i + 1), SETADD(S2, i));
            // ↖是缺的
            if (VACANT(S2, i) && VACANT(S2, i - 1))
                search(originS, SETADD(S1, i), SETADD(S2, i - 1, i));
            // ↗是缺的
            if (VACANT(S2, i) && VACANT(S2, i + 1))
                search(originS, SETADD(S1, i), SETADD(S2, i, i + 1));
            break;
        }
}
#define FOR0(i, n) for (int i = 0; i < n; i++)
int ans[1 << MM][1 << MM];
int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> m;
    memset(a, 0, sizeof(a));
    for (int S = 0; S < (1 << m); S++)
        search(S, S);
    int matsz = (1 << m);
    FOR0(i, matsz) FOR0(j, matsz) ans[i][j] = (i == j) ? 1 : 0;
    //矩阵快速幂 ans=a^(n-1)
    long long b = n - 1;
    while (b) {
        if (b & 1)
            mat_mul(ans, a);
        mat_mul(a, a);
        b >>= 1;
    }
    printf("%d\n", ans[0][matsz - 1]);
    return 0;
}