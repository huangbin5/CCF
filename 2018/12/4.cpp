/**
 * 就是一颗最小生成树。。。记录树中的最长边就好了
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// #define DEBUG

const int maxn = 50005;
const int INF = 0x3fffffff;
struct Node {
    int v, d;
    Node(int _v, int _d)
        : v(_v)
        , d(_d) {}
    bool operator<(const Node& node) const { return d > node.d; }
};
vector<Node> edge[maxn];
int dis[maxn];
bool vis[maxn] = { false };
int n, m, r, ans = 0;

void prim() {
    fill(dis, dis + maxn, INF);
    dis[r] = 0;
    priority_queue<Node> pq;
    pq.push(Node(r, 0));
    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();
        int u = node.v;
        if (vis[u])
            continue;
        if (node.d > ans)
            ans = node.d;
        vis[u] = true;
        for (int i = 0; i < edge[u].size(); ++i) {
            int v = edge[u][i].v, d = edge[u][i].d;
            if (d < dis[v]) {
                dis[v] = d;
                pq.push(Node(v, dis[v]));
            }
        }
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &r);
    int u, v, d;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &d);
        edge[u].push_back(Node(v, d));
        edge[v].push_back(Node(u, d));
    }
    prim();
    printf("%d", ans);
    return 0;
}