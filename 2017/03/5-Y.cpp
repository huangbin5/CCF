#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxn = 5000;
const ll INF = 0x3f3f3f3f3f3f3f3fLL;
int n, m, A, B, Q, X, col[maxn][maxn], row[maxn][maxn];
long long dp[maxn], v;

int main() {
    scanf("%d%d%d%d%d%d", &n, &m, &A, &B, &Q, &X);
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < m; ++j)
            col[j][i] = X = ((ll)A * X + B) % Q;
    for (int i = 1; i <= n - 2; ++i)
        for (int j = 0; j < m - 1; ++j)
            row[j][i] = X = ((ll)A * X + B) % Q;
    for (int i = 0; i < n - 1; ++i)
        dp[i] = col[0][i];
    for (int i = 1; i < n - 1; ++i)
        dp[i] = min(dp[i], dp[i - 1] + row[0][i]);
    for (int i = n - 3; i >= 0; --i)
        dp[i] = min(dp[i], dp[i + 1] + row[0][i + 1]);
    for (int i = 1; i < m; ++i) {
        for (int j = 0; j < n - 1; ++j)
            dp[j] += col[i][j];
        for (int j = 1; j < n - 1; ++j)
            dp[j] = min(dp[j], dp[j - 1] + row[i][j]);
        for (int j = n - 3; j >= 0; --j)
            dp[j] = min(dp[j], dp[j + 1] + row[i][j + 1]);
    }
    ll res = INF;
    for (int i = 0; i < n - 1; ++i)
        res = min(res, dp[i]);
    printf("%lld\n", res);
    return 0;
}