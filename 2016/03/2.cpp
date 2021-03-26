#include <iostream>
using namespace std;
// #define DEBUG

int board[15][10], block[4][4];
//对于每一列最深的行
int maxRow[10];
//最终方块左上角的坐标
int ansCol, ansRow = 14;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    for (int i = 0; i < 10; ++i)
        maxRow[i] = 15;
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 10; ++j) {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 1 && maxRow[j] == 15)
                maxRow[j] = i;
        }
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            scanf("%d", &block[i][j]);
    scanf("%d", &ansCol);
    --ansCol;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            if (block[i][j] == 1) {
                //找到能落下最深的行
                int tmp = maxRow[j + ansCol] - i - 1;
                if (tmp < ansRow)
                    ansRow = tmp;
            }
        }
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            //将方块填入棋盘
            if (block[i][j] == 1)
                board[ansRow + i][ansCol + j] = 1;
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 10; ++j)
            if (j == 9)
                printf("%d\n", board[i][j]);
            else
                printf("%d ", board[i][j]);
    return 0;
}