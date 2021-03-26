#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

int board[3][3];
int T;

int check() {
    for (int i = 0; i < 3; ++i) {
        //列
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != 0)
            return board[0][i];
        //行
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != 0)
            return board[i][0];
    }
    //主对角线
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != 0)
        return board[0][0];
    //副对角线
    if (board[1][1] == board[0][2] && board[1][1] == board[2][0] && board[1][1] != 0)
        return board[1][1];
    return 0;
}

// turn=-10轮到Alice，turn=10轮到Bob
int dfs(int remain, int turn) {
    int ans = check();
    //可以区分胜负
    if (ans != 0)
        return ans == 1 ? remain + 1 : -(remain + 1);
    //平局
    if (remain == 0)
        return 0;
    ans = turn;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            //对每一个空格dfs，如果是Alice则取最大的，如果是Bob则取负的最大的即最小的
            if (board[i][j] == 0) {
                if (turn < 0) {
                    board[i][j] = 1;
                    /**
                     * 最开始是这里没想通，花了很长的时间！！！
                     */
                    ans = max(ans, dfs(remain - 1, -turn));
                } else {
                    board[i][j] = 2;
                    ans = min(ans, dfs(remain - 1, -turn));
                }
                //回溯
                board[i][j] = 0;
            }
        }
    }
    return ans;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while (T--) {
        //剩余空格数
        int remain = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                scanf("%d", &board[i][j]);
                if (board[i][j] == 0)
                    ++remain;
            }
        }
        /**
         * 一开始我还把坐标带上了，糊涂！！！
         */
        printf("%d\n", dfs(remain, -10));
    }
    return 0;
}