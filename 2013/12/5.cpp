#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 55;
char board[maxn][maxn];
//记录起点能到达的位置
bool sflag[maxn][maxn] = { false };
//记录终点能到达的位置
bool tflag[maxn][maxn] = { false };
int r, c, si, sj, ti, tj;

bool legal(int i, int j) {
    if (i < 0 || i >= r || j < 0 || j >= c || board[i][j] == '#')
        return false;
    return true;
}

//找到起点能到达的位置
void tagSflag(int i, int j) {
    sflag[i][j] = true;
    //依次访问上下左右节点
    if (board[i][j] != '-') {
        if (board[i][j] != '.') {
            //下一个节点未被访问，则访问
            if (legal(i - 1, j) && !sflag[i - 1][j])
                tagSflag(i - 1, j);
        }
        if (legal(i + 1, j) && !sflag[i + 1][j])
            tagSflag(i + 1, j);
    }
    if (board[i][j] != '|' && board[i][j] != '.') {
        if (legal(i, j - 1) && !sflag[i][j - 1])
            tagSflag(i, j - 1);
        if (legal(i, j + 1) && !sflag[i][j + 1])
            tagSflag(i, j + 1);
    }
}

//找到能到达终点的位置
void tagTflag(int i, int j) {
    tflag[i][j] = true;
    if (legal(i - 1, j) && board[i - 1][j] != '-' && !tflag[i - 1][j])
        tagTflag(i - 1, j);
    if (legal(i + 1, j) && board[i + 1][j] != '-' && board[i + 1][j] != '.' && !tflag[i + 1][j])
        tagTflag(i + 1, j);
    if (legal(i, j - 1) && board[i][j - 1] != '|' && board[i][j - 1] != '.' && !tflag[i][j - 1])
        tagTflag(i, j - 1);
    if (legal(i, j + 1) && board[i][j + 1] != '|' && board[i][j + 1] != '.' && !tflag[i][j + 1])
        tagTflag(i, j + 1);
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &r, &c);
    for (int i = 0; i < r; ++i) {
        getchar();
        for (int j = 0; j < c; ++j) {
            board[i][j] = getchar();
            if (board[i][j] == 'S') {
                si = i;
                sj = j;
            }
            if (board[i][j] == 'T') {
                ti = i;
                tj = j;
            }
        }
    }
    tagSflag(si, sj);
    tagTflag(ti, tj);
    if (!tflag[si][sj])
        printf("I'm stuck!");
    else {
        int ans;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (sflag[i][j] && !tflag[i][j])
                    ++ans;
            }
        }
        printf("%d", ans);
    }
    return 0;
}