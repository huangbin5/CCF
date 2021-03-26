/**
 * 自己的错误解法：
 * 数据规模已达到复杂度的上限，很明显不能对每个点都做一次spfa
 */
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
#define DEBUG

const int maxn = 1005;
const int INF = 0x3fffffff;
struct Node {
    int x, y;
    Node() {}
    Node(int _x, int _y)
        : x(_x)
        , y(_y) {}
};
//-2表示障碍物，-1表示门店，其它表示订餐数量
int matrix[maxn][maxn] = { 0 };
vector<Node> customer;
int dis[maxn][maxn];
bool inq[maxn][maxn];
bool vis[maxn][maxn] = { false };
//表示节点路径上的前驱，-1表示没有前驱
int pre[maxn][maxn];
int n, m, k, d;
//终点
int tx, ty;
ll fee = 0;

int direc[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

bool legal(int x, int y) {
    if (x >= 1 && x <= n && y >= 1 && y <= n && matrix[x][y] != -2)
        return true;
    return false;
}

void spfa(int x, int y) {
    fill(dis[0], dis[0] + maxn * maxn, INF);
    memset(inq, false, sizeof(inq));
    dis[x][y] = 0;
    pre[x][y] = -1;
    queue<Node> q;
    q.push(Node(x, y));
    inq[x][y] = true;
    while (!q.empty()) {
        Node node = q.front();
        q.pop();
        inq[node.x][node.y] = false;
        for (int i = 0; i < 4; ++i) {
            int nx = node.x + direc[i][0], ny = node.y + direc[i][1];
            if (legal(nx, ny) && dis[node.x][node.y] + 1 < dis[nx][ny]) {
                dis[nx][ny] = dis[node.x][node.y] + 1;
                pre[nx][ny] = (i + 2) % 4;
                //如果是门店
                if (matrix[nx][ny] == -1) {
                    tx = nx;
                    ty = ny;
                    return;
                }
                if (!inq[nx][ny]) {
                    q.push(Node(nx, ny));
                    inq[nx][ny] = true;
                }
            }
        }
    }
}

void cacul() {
    int nx = tx, ny = ty;
    while (pre[nx][ny] != -1) {
        if (matrix[nx][ny] >= 0 && !vis[nx][ny]) {
            fee += (ll)matrix[nx][ny] * (dis[tx][ty] - dis[nx][ny]);
            vis[nx][ny] = true;
        }
        int dir = pre[nx][ny];
        nx += direc[dir][0];
        ny += direc[dir][1];
    }
    fee += (ll)matrix[nx][ny] * (dis[tx][ty] - dis[nx][ny]);
    vis[nx][ny] = true;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &k, &d);
    int x, y, num;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &x, &y);
        matrix[x][y] = -1;
    }
    for (int i = 0; i < k; ++i) {
        scanf("%d%d%d", &x, &y, &num);
        if (matrix[x][y] == 0)
            customer.push_back(Node(x, y));
        matrix[x][y] += num;
    }
    for (int i = 0; i < d; ++i) {
        scanf("%d%d", &x, &y);
        matrix[x][y] = -2;
    }
    printf("%d\n", customer.size());
    for (int i = 0; i < customer.size(); ++i) {
        Node node = customer[i];
        if (!vis[node.x][node.y]) {
            printf("%d\n", i);
            spfa(node.x, node.y);
            cacul();
        }
    }
    printf("%lld\n", fee);
    return 0;
}