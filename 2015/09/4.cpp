#include <cstring>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
// #define DEBUG

const int maxn = 10005;
vector<int> edge[maxn];
int dTime[maxn], lowlink[maxn], scc[maxn];
int curTime, sccNo, n, ans;
stack<int> s;

void dfs(int u) {
    dTime[u] = lowlink[u] = ++curTime;
    s.push(u);
    for (int i = 0; i < edge[u].size(); ++i) {
        int v = edge[u][i];
        if (!dTime[v]) {
            dfs(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else if (!scc[v])
            lowlink[u] = min(lowlink[u], lowlink[v]);
    }
    if (lowlink[u] == dTime[u]) {
        ++sccNo;
        int sccSize = 0;
        for (;;) {
            int x = s.top();
            s.pop();
            scc[x] = sccNo;
            ++sccSize;
            if (x == u)
                break;
        }
        ans += sccSize * (sccSize - 1) / 2;
    }
}

void findScc() {
    curTime = sccNo = 0;
    memset(scc, 0, sizeof(scc));
    memset(dTime, 0, sizeof(dTime));
    for (int i = 1; i <= n; ++i)
        if (!dTime[i])
            dfs(i);
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    int m, u, v;
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
    }
    findScc();
    printf("%d", ans);
    return 0;
}