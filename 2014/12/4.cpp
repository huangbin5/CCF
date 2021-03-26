#include <iostream>
#include <vector>
using namespace std;
// #define DEBUG

const int maxn = 1005;
const int INF = 0x3fffffff;
struct Node {
    int v, dis;
    Node() {}
    Node(int _v, int _dis)
        : v(_v)
        , dis(_dis) {}
};
int n, m;
vector<Node> edge[maxn];
int dis[maxn];
bool vis[maxn] = { false };

int prim() {
    fill(dis, dis + maxn, INF);
    dis[1] = 0;
    // 返回最小生成树边的总权值
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int u = -1;
        for (int j = 1; j <= n; ++j)
            if (!vis[j] && (u == -1 || dis[j] < dis[u]))
                u = j;
        if (u == -1)
            return -1;
        vis[u] = true;
        // 累计权值
        ans += dis[u];
        for (int j = 0; j < edge[u].size(); ++j) {
            int v = edge[u][j].v, e = edge[u][j].dis;
            if (!vis[v] && e < dis[v])
                dis[v] = e;
        }
    }
    return ans;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    int u, v, e;
    while (m--) {
        scanf("%d%d%d", &u, &v, &e);
        edge[u].push_back(Node(v, e));
        edge[v].push_back(Node(u, e));
    }
    printf("%d", prim());
    return 0;
}