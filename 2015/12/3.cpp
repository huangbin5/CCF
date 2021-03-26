#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;
#define DEBUG

const int maxn = 105;
const int direc[][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
char board[maxn][maxn];
bool vis[maxn][maxn];
int n, m, q;

void handle0(int x1, int y1, int x2, int y2) {
    if (x2 < x1)
        swap(x1, x2);
    if (y2 < y1)
        swap(y1, y2);
    if (x1 == x2) {
        for (int y = y1; y <= y2; ++y) {
            //注意不能只判断='|'的情况，还有'+'的情况
            if (board[x1][y] == '|' || board[x1][y] == '+')
                board[x1][y] = '+';
            else
                board[x1][y] = '-';
        }
    }
    if (y1 == y2) {
        for (int x = x1; x <= x2; ++x) {
            if (board[x][y1] == '-' || board[x][y1] == '+')
                board[x][y1] = '+';
            else
                board[x][y1] = '|';
        }
    }
}

bool valid(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m && board[x][y] != '-' && board[x][y] != '|' && board[x][y] != '+')
        return true;
    return false;
}

void handle1(int x, int y, char c) {
    memset(vis, false, sizeof(vis));
    board[x][y] = c;
    vis[x][y] = true;
    queue<pair<int, int>> qu;
    qu.push(make_pair(x, y));
    while (!qu.empty()) {
        pair<int, int> pa = qu.front();
        qu.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = pa.first + direc[i][0], ny = pa.second + direc[i][1];
            if (!vis[nx][ny] && valid(nx, ny)) {
                board[nx][ny] = c;
                vis[nx][ny] = true;
                qu.push(make_pair(nx, ny));
            }
        }
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    fill(board[0], board[0] + maxn * maxn, '.');
    scanf("%d%d%d", &m, &n, &q);
    int type, x1, y1, x2, y2;
    char c;
    while (q--) {
        scanf("%d", &type);
        //按照习惯，调换x和y的顺序
        if (type == 0) {
            scanf("%d%d%d%d", &y1, &x1, &y2, &x2);
            handle0(x1, y1, x2, y2);
        } else {
            scanf("%d%d %c", &y1, &x1, &c);
            handle1(x1, y1, c);
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < m; ++j)
            //不要习惯性地每两个字符之间输出一个空格
            printf("%c", board[i][j]);
        puts("");
    }
    return 0;
}