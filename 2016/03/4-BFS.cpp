#include <iostream>
#include <queue>
using namespace std;
// #define DEBUG

const int maxn = 105;
const int direc[][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
struct Node {
    int x, y, t;
    Node() {}
    Node(int _x, int _y, int _t)
        : x(_x)
        , y(_y)
        , t(_t) {}
};
//时间维度要是300以上
bool vis[maxn][maxn][maxn * 3] = { 0 };
int n, m, d;

bool valid(int x, int y) {
    if (x >= 1 && x <= n && y >= 1 && y <= m)
        return true;
    return false;
}

int bfs() {
    queue<Node> q;
    q.push(Node(1, 1, 0));
    vis[1][1][0] = 1;
    while (!q.empty()) {
        Node node = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = node.x + direc[i][0];
            int ny = node.y + direc[i][1];
            int nt = node.t + 1;
            if (nx == n && ny == m)
                return nt;
            if (valid(nx, ny) && !vis[nx][ny][nt]) {
                q.push(Node(nx, ny, nt));
                vis[nx][ny][nt] = 1;
            }
        }
    }
    return -1;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &d);
    int x, y, a, b;
    while (d--) {
        scanf("%d%d%d%d", &x, &y, &a, &b);
        for (int i = a; i <= b; ++i)
            vis[x][y][i] = 1;
    }
    printf("%d", bfs());
    return 0;
}