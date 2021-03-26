#include <iostream>
#include <vector>
using namespace std;
// #define DEBUG

const int maxn = 10005;
const int INF = 0x3fffffff;
struct Node {
    int v, e;
    Node() {}
    Node(int _v, int _e)
        : v(_v)
        , e(_e) {}
};
vector<Node> edge[maxn];
// dis-到首都的距离，cost-到上一个城市的距离
int dis[maxn], cost[maxn];
bool vis[maxn];
int n, m;

void init() {
    for (int i = 0; i < maxn; ++i) {
        dis[i] = INF;
        vis[i] = false;
    }
}

int dijkstra() {
    init();
    int ans = 0;
    dis[1] = 0;
    cost[1] = 0;
    for (int i = 0; i < n; ++i) {
        int u = -1;
        for (int j = 1; j <= n; ++j)
            if (!vis[j] && (u == -1 || dis[j] < dis[u]))
                u = j;
        vis[u] = true;
        ans += cost[u];
        for (int j = 0; j < edge[u].size(); ++j) {
            int v = edge[u][j].v, e = edge[u][j].e;
            //若到首都的距离相等，则选更短的那一段铁路
            if (!vis[v] && (dis[u] + e < dis[v]) || (dis[u] + e == dis[v] && e < cost[v])) {
                dis[v] = dis[u] + e;
                cost[v] = e;
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
    scanf("%d%d", &n, &m);
    int u, v, e;
    while (m--) {
        scanf("%d%d%d", &u, &v, &e);
        edge[u].push_back(Node(v, e));
        edge[v].push_back(Node(u, e));
    }
    printf("%d", dijkstra());
    return 0;
}