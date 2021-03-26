#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 505;
int board[maxn][maxn];
int n, i, j;
bool up = true;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            scanf("%d", &board[i][j]);
        }
    }
    i = 0, j = 0;
    while (i != n - 1 || j != n - 1) {
        printf("%d ", board[i][j]);
        if (up) {
            if (j == n - 1) {
                ++i;
                up = false;
            } else if (i == 0) {
                ++j;
                up = false;
            } else {
                --i;
                ++j;
            }
        } else {
            if (i == n - 1) {
                ++j;
                up = true;
            } else if (j == 0) {
                ++i;
                up = true;
            } else {
                ++i;
                --j;
            }
        }
    }
    printf("%d", board[i][j]);
    return 0;
}