/**
 * 石子合并问题
 * sum[i][j]表示第i堆到第j堆总的石子数
 * sum[i][j] = sum[i][k] + sum[k+1][j]
 * dp[i][j]表示第i堆石子到第j堆石子合并的花费
 * dp[i][j] = min{dp[i][k], dp[k+1][j]} + sum[i][j]
 */
#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1005;
const int INF = 0x3fffffff;
int num[maxn], sum[maxn];
int dp[maxn][maxn], pro[maxn][maxn];
int n;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &num[i]);
    fill(dp[0], dp[0] + maxn * maxn, INF);
    // dp起点
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 0;
        sum[i] = sum[i - 1] + num[i];
        pro[i][i] = i;
    }
    //对区间长度递增
    for (int len = 1; len < n; ++len) {
        for (int i = 0; i + len < n; ++i) {
            int j = i + len;
            for (int k = pro[i][j - 1]; k <= pro[i + 1][j]; ++k) {
                int tmp = dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1];
                if (tmp < dp[i][j]) {
                    dp[i][j] = tmp;
                    pro[i][j] = k;
                }
            }
        }
    }
    printf("%d", dp[0][n - 1]);
    return 0;
}