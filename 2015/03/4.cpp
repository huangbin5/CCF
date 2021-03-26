#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// #define DEBUG

//n和m都是10000，总共是20000
const int maxn = 20005;
vector<int> edge[maxn];
int level[maxn];
bool vis[maxn];
int n, m, maxLevel;

void bfs(int s) {
    memset(level, 0, sizeof(level));
    memset(vis, false, sizeof(vis));
    level[s] = 0;
    vis[s] = true;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < edge[u].size(); ++i) {
            int v = edge[u][i];
            if (!vis[v]) {
                level[v] = level[u] + 1;
                maxLevel = level[v];
                vis[v] = true;
                q.push(v);
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
    int tmp;
    for (int i = 2; i <= n + m; ++i) {
        scanf("%d", &tmp);
        edge[i].push_back(tmp);
        edge[tmp].push_back(i);
    }
    bfs(1);
    for (int i = 1; i <= n + m; ++i) {
        if (level[i] == maxLevel) {
            bfs(i);
            printf("%d", maxLevel);
            return 0;
        }
    }
    return 0;
}