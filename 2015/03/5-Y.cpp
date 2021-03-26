#include <bits/stdc++.h>

using namespace std;
#define DEBUG

typedef long long LL;
typedef pair<int, int> pii;
#define FI first
#define SE second
#define for_edge(u, it) for (vector<pii>::iterator it = G[u].begin(); it != G[u].end(); ++it)

const int N = 100000 + 10;

//邻接表
vector<pii> G[N];
// m个询问
pii q_info[N];
// Q-有效询问的编号
vector<int> Q[N], q1[N], q2[N];
LL dis[N], disv[N];
int cost[N], sz[N], maxsz[N], top[N], root;
//最小花费即答案
pair<LL, int> ans[N];
bool centre[N];

#define v it->FI
void get_size(int u, int fa) {
    maxsz[u] = 0, sz[u] = 1;
    for_edge(u, it) if (v != fa && !centre[v]) {
        get_size(v, u);
        sz[u] += sz[v];
        maxsz[u] = max(maxsz[u], sz[v]);
    }
}

void get_root(int u, int fa, int r) {
    maxsz[u] = max(maxsz[u], sz[r] - sz[u]);
    if (maxsz[u] < maxsz[root])
        root = u;
    for_edge(u, it) if (v != fa && !centre[v]) { get_root(v, u, r); }
}

int anc[17][N], val[17][N];

int tot_time;

void get_top(int u, int fa, int pre) {
    anc[0][u] = fa, val[0][u] = cost[u];
    int tmp = clock();
    for (int i = 1; i < 17; i++) {
        val[i][u] = min(val[i - 1][u], val[i - 1][anc[i - 1][u]]);
        anc[i][u] = anc[i - 1][anc[i - 1][u]];
    }
    tot_time += clock() - tmp;

    top[u] = pre;
    for_edge(u, it) if (v != fa && !centre[v]) { dis[v] = dis[u] + it->SE, get_top(v, u, pre); }
}

int pre[N];

int find(int u) {
    int cost_u = cost[u];
    // int tmp = clock();
    for (int i = 16; i >= 0; i--) {
        if (val[i][u] >= cost_u)
            u = anc[i][u];
    }
    // tot_time += clock() - tmp;
    return u;
}

void calc_1(int u, int fa) {
    int anc = find(u);

    if (anc)
        pre[u] = pre[anc];
    else
        anc = root, pre[u] = u; // be root when not exist
    disv[u] = (dis[u] - dis[anc]) * cost[u] + disv[anc];

    for (unsigned i = 0; i < q1[u].size(); i++) {
        ans[q1[u][i]] = make_pair(disv[u], cost[pre[u]]);
    }

    for_edge(u, it) if (v != fa && !centre[v]) { calc_1(v, u); }
}

void calc_2(int u, int fa, int fee) {
    static int val[N], id[N], tot;
    disv[u] = (dis[u] - dis[fa]) * fee + disv[fa];
    id[tot] = u, val[tot] = cost[u];
    if (tot++)
        val[tot - 1] = min(val[tot - 2], cost[u]);

    id[tot] = u; // be u when not exist
    for (unsigned i = 0; i < q2[u].size(); i++) {
        int c = q2[u][i];
        int anc = id[lower_bound(val, val + tot, ans[c].SE, greater<int>()) - val];
        ans[c].FI += ans[c].SE * (dis[anc] - dis[root]) + disv[u] - disv[anc];
    }

    for_edge(u, it) if (v != fa && !centre[v]) { calc_2(v, u, min(fee, cost[u])); }
    --tot;
}

void solve(int u) {
    if (!Q[u].size())
        return;

    get_size(u, 0);
    root = u, get_root(u, 0, u);
    // cerr << sz[u] << ' ' << maxsz[root] << endl;

    vector<int> vec_q;
    vec_q.swap(Q[u]);

    centre[u = root] = 1, top[u] = u, dis[u] = 0;
    for (int i = 0; i < 17; i++)
        anc[i][u] = val[i][u] = 0;
    val[0][u] = cost[u];
    for_edge(u, it) if (!centre[v]) { dis[v] = it->SE, get_top(v, u, v); }

    for (unsigned i = 0; i < vec_q.size(); i++) {
        int c = vec_q[i], x = q_info[c].FI, y = q_info[c].SE;
        if (top[x] == top[y])
            Q[top[x]].push_back(c);
        else
            q1[x].push_back(c), q2[y].push_back(c);
    }

    disv[u] = 0, pre[u] = u;
    calc_1(u, 0);

    disv[u] = 0;
    calc_2(root, 0, cost[u]);

    for (unsigned i = 0; i < vec_q.size(); i++) {
        int c = vec_q[i], x = q_info[c].FI, y = q_info[c].SE;
        q1[x].clear(), q2[y].clear();
    }

    for_edge(u, it) if (!centre[v]) { solve(v); }
}
#undef v

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
    int start_time = clock();
#endif

    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", cost + i);
    }
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(pii(v, w));
        G[v].push_back(pii(u, w));
    }

    for (int i = 0; i < m; i++) {
        pii& cur = q_info[i];
        scanf("%d%d", &cur.FI, &cur.SE);
        if (cur.FI != cur.SE)
            Q[1].push_back(i);
    }

    solve(1);

    for (int i = 0; i < m; i++) {
        printf("%I64d\n", ans[i].FI);
    }
#ifdef DEBUG
    printf("time used : %.5fs, %.5fs\n", (double)(clock() - start_time) / CLOCKS_PER_SEC, (double)tot_time / CLOCKS_PER_SEC);
    // system("pause");
#endif
    return 0;
}