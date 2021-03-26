#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// #define DEBUG

const int maxn = 100005;
const int INF = 0x3fffffff;
struct Node {
    int v, c;
    Node() {}
    Node(int _v, int _c)
        : v(_v)
        , c(_c) {}
};
vector<Node> edge[maxn];
// cost[i]表示节点i到节点1路径上最大的边的最小值
int cost[maxn];
bool inq[maxn] = { false };
int n, m;

void spfa() {
    for (int i = 1; i <= n; ++i)
        cost[i] = INF;
    queue<int> q;
    cost[1] = 0;
    q.push(1);
    inq[1] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int i = 0; i < edge[u].size(); ++i) {
            int v = edge[u][i].v, c = edge[u][i].c;
            if (max(cost[u], c) < cost[v]) {
                cost[v] = max(cost[u], c);
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
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
    int u, v, c;
    while (m--) {
        scanf("%d%d%d", &u, &v, &c);
        edge[u].push_back(Node(v, c));
        edge[v].push_back(Node(u, c));
    }
    spfa();
    printf("%d", cost[n]);
    return 0;
}