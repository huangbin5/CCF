/**
 * 只需要向两个方向分别dfs或bfs一次，看是否能到达所有的顶点即可
 * v = 10 ^ 3, e = 10 ^ 4
 * 若使用邻接矩阵，时间复杂度为 2 * v * (v ^ 2) = 2 * 10 ^ 9 = 20s
 * 若使用邻接表，时间复杂度为 v * (v + e) = 2 * 10 ^ 6 * 11 = 0.22s = 220ms
 * 对于邻接表，若只记录题目所给的有向边，则逆向遍历的时候寻找相邻的点会很麻烦
 * 因此可以将逆向边保持在另一个邻接表中！
 */
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// #define DEBUG

const int maxn = 1005;
vector<int> edge1[maxn], edge2[maxn];
bool vis1[maxn], vis2[maxn];
int n, m;

void dfs(int u, int flag) {
    bool* vis = flag ? vis1 : vis2;
    vector<int>* edge = flag ? edge1 : edge2;
    vis[u] = true;
    for (int i = 0; i < edge[u].size(); ++i) {
        int v = edge[u][i];
        if (!vis[v])
            dfs(v, flag);
    }
}

void bfs(int x, int flag) {
    bool* vis = flag ? vis1 : vis2;
    vector<int>* edge = flag ? edge1 : edge2;
    queue<int> q;
    q.push(x);
    vis[x] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < edge[u].size(); ++i) {
            int v = edge[u][i];
            if (!vis[v]) {
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
    scanf("%d%d", &n, &m);
    int u, v;
    while (m--) {
        scanf("%d%d", &u, &v);
        edge1[u].push_back(v);
        edge2[v].push_back(u);
    }
    int ans = 0;
    bool flag;
    for (int i = 1; i <= n; ++i) {
        flag = true;
        memset(vis1, false, sizeof(vis1));
        memset(vis2, false, sizeof(vis2));
        for (int k = 0; k < 2; ++k)
            dfs(i, k);
            // bfs(i, k);
        for (int j = 1; j <= n; ++j)
            if (!vis1[j] && !vis2[j]) {
                flag = false;
                break;
            }
        if (flag)
            ++ans;
    }
    printf("%d", ans);
    return 0;
}