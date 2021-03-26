/**
 * 70分
 * 轮廓线动态规划：除了最后3组超大数据超时外都通过了
 */
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 8;
const int MOD = 1000000007;
ll dp[2][1 << maxn];
int n, m, cur, powm;

void update(int a, int b) {
    // b的最高位要被填充
    if (b & (powm << 1))
        // b清0; 记得要取余
        dp[cur][b ^ (powm << 1)] = (dp[cur][b ^ (powm << 1)] + dp[1 - cur][a]) % MOD;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    // 2 ^ m
    powm = 1 << m;
    memset(dp, 0, sizeof(dp));
    cur = 0;
    //虚拟的一行必须全部填满
    dp[cur][(powm << 1) - 1] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            //处理下一格
            cur ^= 1;
            memset(dp[cur], 0, sizeof(dp[cur]));
            if (i == 2 && j == 1)
                int x = 0;
            for (int k = 0; k < (powm << 1); ++k) {
                // 1、不放积木
                update(k, k << 1);
                if (i && j) {
                    // 2、放左上角缺失的积木
                    //上面和左边的需为空
                    if (!(k & (powm >> 1)) && !(k & 1))
                        //将上面和左边和该格填充
                        update(k, (k << 1) ^ powm ^ 3);
                    // 3、放右上角缺失的积木
                    //左上和左边的需为空
                    //易漏：当为最后一列时上面的不为空
                    if ((j != m - 1 || k & (powm >> 1)) && !(k & powm) && !(k & 1))
                        //将左上和左边和该格填充
                        update(k, (k << 1) ^ (powm << 1) ^ 3);
                    // 4、放左下角缺失的积木
                    //左上和上面的需为空
                    if (!(k & powm) && !(k & (powm >> 1)))
                        //将左上和上面和该格填充
                        update(k, (k << 1) ^ (powm << 1) ^ powm ^ 1);
                    // 5、放右下角缺失的积木
                    //左上和上面和左边的需为空
                    if (!(k & powm) && !(k & (powm >> 1)) && !(k & 1))
                        //将左上和上面和左边填充
                        update(k, (k << 1) ^ (powm << 1) ^ powm ^ 2);
                }
            }
        }
    }
    printf("%d", dp[cur][(powm << 1) - 1]);
    return 0;
}