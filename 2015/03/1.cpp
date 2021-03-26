#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1005;
int mt[maxn][maxn];
int n, m;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &mt[i][j]);
        }
    }
    for (int i = m - 1; i >= 0; --i) {
        for (int j = 0; j < n; ++j) {
            if (j)
                printf(" %d", mt[j][i]);
            else
                printf("%d", mt[j][i]);
        }
        puts("");
    }
    return 0;
}