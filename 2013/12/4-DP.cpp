/**
 * 方法源自网络，我是想不到这么划分状态
 */
#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 1005;
const int p = 1000000007;
ll dp[maxn][6] = { 0 }, n;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    /**
     * 状态0：只填了2
     * 状态1：只填了2 0
     * 状态2：只填了2 3
     * 状态3：只填了2 0 1
     * 状态4：只填了2 0 3
     * 状态5：只填了2 0 1 3，即全部填了
     */
    dp[1][0] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i][0] = dp[i - 1][0];
        dp[i][1] = (dp[i - 1][0] + dp[i - 1][1] * 2) % p;
        dp[i][2] = (dp[i - 1][0] + dp[i - 1][2]) % p;
        dp[i][3] = (dp[i - 1][1] + dp[i - 1][3] * 2) % p;
        dp[i][4] = (dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][4] * 2) % p;
        dp[i][5] = (dp[i - 1][3] + dp[i - 1][4] + dp[i - 1][5] * 2) % p;
    }
    printf("%d", dp[n][5]);
    return 0;
}