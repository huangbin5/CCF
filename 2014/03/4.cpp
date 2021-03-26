/**
 * 想到了把它转化成无向图然后用BFS
 * 但一直卡在如果最优路径上包含的新增点数多余k怎么办
 * （其实只需要给每个顶点记录路径上使用了新增点的个数
 * 当个数大于k时便不能走这条路了）
 */
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 205;
struct Node {
    int x, y;
    //是否已存在的节点
    int exist;
    // 路径上新增节点的个数，bfs层次
    int cnt, level;
    Node() {}
    Node(int _x, int _y, int _exist)
        : x(_x)
        , y(_y)
        , exist(_exist) {}
} node[maxn];
int matrix[maxn][maxn] = { 0 };
bool vis[maxn] = { false };
int n, m, k;
ll r;

int adjacent(Node& a, Node& b) {
    // 10^8 * 10^8要用long long保存
    ll dx = a.x - b.x, dy = a.y - b.y;
    if (dx * dx + dy * dy <= r * r)
        return 1;
    return 0;
}

void bfs() {
    queue<int> q;
    node[1].cnt = 0;
    node[1].level = 0;
    q.push(1);
    vis[1] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 1; v <= n + m; ++v) {
            if (!vis[v] && matrix[u][v] == 1) {
                node[v].cnt = node[u].cnt;
                //如果是新增节点则cnt要加1
                if (node[v].exist == 0) {
                    ++node[v].cnt;
                    if (node[v].cnt > k)
                        continue;
                }
                node[v].level = node[u].level + 1;
                q.push(v);
                vis[v] = true;
            }
        }
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d%d%lld", &n, &m, &k, &r);
    int x, y;
    for (int i = 1; i <= n + m; ++i) {
        scanf("%d%d", &x, &y);
        if (i <= n)
            node[i] = Node(x, y, 1);
        else
            node[i] = Node(x, y, 0);
        for (int j = 1; j < i; ++j) {
            //维护邻接关系
            matrix[i][j] = matrix[j][i] = adjacent(node[i], node[j]);
        }
    }
    bfs();
    printf("%d", node[2].level - 1);
    return 0;
}