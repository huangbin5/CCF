/**
 * 从来没有遇到过多个起点的bfs，也没往这方面去思考
 * 说明对bfs的理解和敏感度还不够
 * 遇见了一次就要牢牢把握
 */
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 1005;
struct Node {
    int x, y;
    Node() {}
    Node(int _x, int _y)
        : x(_x)
        , y(_y) {}
};
//表示订餐数量
int matrix[maxn][maxn] = { 0 };
int dis[maxn][maxn];
bool vis[maxn][maxn] = { false };
int n, m, k, d;
ll fee = 0;

int direc[][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

bool legal(int x, int y) {
    if (x >= 1 && x <= n && y >= 1 && y <= n)
        return true;
    return false;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &k, &d);
    int x, y, num;
    queue<Node> q;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &x, &y);
        //所有门店都入队
        q.push(Node(x, y));
        dis[x][y] = 0;
        vis[x][y] = true;
    }
    for (int i = 0; i < k; ++i) {
        scanf("%d%d%d", &x, &y, &num);
        matrix[x][y] += num;
    }
    for (int i = 0; i < d; ++i) {
        scanf("%d%d", &x, &y);
        //障碍物不在bfs过程中入队
        vis[x][y] = true;
    }
    //计算每个点距离门店的最短距离
    while (!q.empty()) {
        Node node = q.front();
        q.pop();
        //如果有订餐数目
        if (matrix[node.x][node.y] > 0)
            fee += dis[node.x][node.y] * matrix[node.x][node.y];
        for (int i = 0; i < 4; ++i) {
            int nx = node.x + direc[i][0], ny = node.y + direc[i][1];
            if (legal(nx, ny) && !vis[nx][ny]) {
                q.push(Node(nx, ny));
                dis[nx][ny] = dis[node.x][node.y] + 1;
                vis[nx][ny] = true;
            }
        }
    }
    printf("%lld\n", fee);
    return 0;
}