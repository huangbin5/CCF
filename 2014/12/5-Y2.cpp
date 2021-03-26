#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>
#define DEBUG
const int maxn = 3007;
const int maxm = 300003;
const int inf = 0x3f3f3f3f;

int map[maxn][maxn];
int v[maxn], w[maxn];
int a[maxn][11], b[maxn][11];

int _flow_cur, _cost_cur;

struct Edge {
    int u, v, cap, cost, next;
    Edge() {}
    Edge(int u, int v, int cap, int cost, int next)
        : u(u)
        , v(v)
        , cap(cap)
        , cost(cost)
        , next(next) {}
} edges[maxm];

int head[maxn], e_cnt;
bool visited[maxn];
int SLK[maxn], dist[maxn], _start_, _end_;

void init() {
    _flow_cur = _cost_cur = 0;
    e_cnt = 0;
    memset(head, -1, sizeof(head));
    memset(visited, 0, sizeof(visited));
}

void add(int u, int v, int cap, int cost) {
    edges[e_cnt] = Edge(u, v, cap, cost, head[u]);
    head[u] = e_cnt++;
    edges[e_cnt] = Edge(v, u, 0, -cost, head[v]);
    head[v] = e_cnt++;
}

bool modlabel() {
    int delta = inf;
    for (int i = 0; i <= _end_; i++) {
        if (!visited[i] && SLK[i] < delta) {
            delta = SLK[i];
            SLK[i] = inf;
        }
    }
    if (delta == inf)
        return false;
    for (int i = 0; i <= _end_; i++) {
        if (visited[i])
            dist[i] += delta;
    }
    return true;
}

int aug(int u, int flow, int pre) {
    if (u == _end_) {
        _cost_cur += flow * dist[_start_];
        return flow;
    }

    visited[u] = true;
    int flow_rest = flow;
    for (int i = head[u]; ~i; i = edges[i].next) {
        register int v = edges[i].v;
        if (!visited[v] && edges[i].cap) {
            int temp = dist[v] + edges[i].cost - dist[u];
            if (!temp) {
                int delta = aug(v, std::min(flow_rest, edges[i].cap), u);
                if (delta > 0) {
                    flow_rest -= delta;
                    edges[i].cap -= delta;
                    edges[i ^ 1].cap += delta;
                }
                if (flow_rest == 0)
                    return flow;
            } else {
                if (temp < SLK[v]) {
                    SLK[v] = temp;
                }
            }
        }
    }

    return flow - flow_rest;
}

void cost_flow() {
    for (int i = 0; i <= _end_; i++) {
        dist[i] = 0;
        SLK[i] = inf;
    }
    do {
        int ret = 0;
        do {
            _flow_cur += ret;
            memset(visited, 0, sizeof(visited));
            ret = aug(_start_, inf, -1);
        } while (ret);
    } while (modlabel());
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    int n, m;
    while (~scanf("%d %d", &n, &m)) {
        init();
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= 6; j++) {
                scanf("%d", &a[i][j]);
            }
            for (int j = 0; j <= 6; j++) {
                scanf("%d", &b[i][j]);
            }
            scanf("%d %d", &v[i], &w[i]);
        }
        memset(map, 0, sizeof(map));
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            map[u][v] = map[v][u] = w;
        }
        int _st = 0, _ed = 14 * n + 1;
        _start_ = _st, _end_ = _ed;
        for (int i = 0; i <= 6; i++) {
            for (int j = 1; j <= n; j++) {
                int id_b = i * n; // 生产点base
                int id_c = (i + 7) * n; // 仓库点base
                if (a[j][i] > b[j][i])
                    add(_st, id_b + j, a[j][i] - b[j][i], 0);
                if (a[j][i] < b[j][i])
                    add(id_b + j, _ed, b[j][i] - a[j][i], 0);
                add(id_b + j, id_c + j, v[j], w[j]);
                int nxt = ((i + 1) % 7) * n; // 下一天的生产点base
                add(id_c + j, nxt + j, inf, 0);
                for (int k = 1; k <= n; k++) {
                    if (!map[j][k])
                        continue;
                    add(id_b + j, id_b + k, inf, map[j][k]);
                    add(id_c + j, nxt + k, inf, map[j][k]);
                }
            }
        }
        cost_flow();
        printf("%d\n", _cost_cur);
    }
}