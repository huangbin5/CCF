#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 1005;
const int p = 1000000007;
ll C[maxn][maxn] = { 0 }, N;

//计算组合数C[n][m]=C[n-1][m]+C[n-1][m-1]
void getC(int n) {
    for (int i = 0; i <= n; ++i) {
        C[i][0] = C[i][i] = 1;
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= i / 2; ++j) {
            C[i][i - j] = C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % p;
        }
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &N);
    getC(N);
    int ans = 0;
    /**
     * 枚举01的总数i从2~n-2，则23的总数为n-i，从除第一个位置以外的n-1个位置中选出i个01的位置
     * 0的个数从1~i-1个共有i-1种，3的个数有1~n-i-1个共n-i-1种
     */
    for (int i = 2; i <= N - 2; ++i) {
        ll tmp = (((C[N - 1][i] * (i - 1)) % p) * (N - i - 1)) % p;
        ans = (ans + tmp) % p;
    }
    printf("%d", ans);
    return 0;
}