#include <iostream>
using namespace std;
#define DEBUG

const int maxn = 105;
int matrix[maxn][maxn] = { 0 };

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    int n, x1, y1, x2, y2;
    scanf("%d", &n);
    while (n--) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        for (int i = x1; i < x2; ++i) {
            for (int j = y1; j < y2; ++j) {
                matrix[i][j] = 1;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < maxn; ++i) {
        for (int j = 0; j < maxn; ++j) {
            ans += matrix[i][j];
        }
    }
    printf("%d", ans);
    return 0;
}