#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 35;
int board[maxn][maxn], flag[maxn][maxn] = { 0 };
int n, m;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", &board[i][j]);
    //只判断右边3格和下面3格是否相同
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j < m - 2 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2])
                flag[i][j] = flag[i][j + 1] = flag[i][j + 2] = 1;
            if (i < n - 2 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j])
                flag[i][j] = flag[i + 1][j] = flag[i + 2][j] = 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (flag[i][j] == 1)
                board[i][j] = 0;
            if (j == m - 1)
                printf("%d\n", board[i][j]);
            else
                printf("%d ", board[i][j]);
        }
    }
    return 0;
}