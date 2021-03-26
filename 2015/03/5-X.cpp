/**
 * 30分
 * 使用dfs，只能过前3个小的测试点
 */
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 100005;
struct Node {
    int v;
    ll e;
    Node() {}
    Node(int _v, ll _e)
        : v(_v)
        , e(_e) {}
};
vector<Node> edge[maxn];
ll cost[maxn];
bool vis[maxn];
int n, m, from, to;

//顶点编号，单价，总价
void dfs(int u, int c, ll t) {
    if (u == to) {
        printf("%lld\n", t);
        return;
    }
    vis[u] = true;
    for (int i = 0; i < edge[u].size(); ++i) {
        int v = edge[u][i].v;
        ll e = edge[u][i].e;
        if (!vis[v])
            dfs(v, cost[v] < c ? cost[v] : c, t + e * c);
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &cost[i]);
    int u, v;
    ll e;
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d%lld", &u, &v, &e);
        edge[u].push_back(Node(v, e));
        edge[v].push_back(Node(u, e));
    }
    while (m--) {
        scanf("%d%d", &from, &to);
        memset(vis, false, sizeof(vis));
        dfs(from, cost[from], 0);
    }
    return 0;
}