#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int maxint = ~0U >> 1;
#define DEBUG

/*
  用法:n节点个数。求解节点0到节点n的费用流
  (1)设置n
  (2)addEdge
  (3)solve()
*/
#define N 1000
#define M 50000
int n, m, pi1, cost = 0;
bool v[N];
struct etype {
    int t, c, u;
    etype *next, *pair;
    etype() {}
    etype(int t_, int c_, int u_, etype* next_)
        : t(t_)
        , c(c_)
        , u(u_)
        , next(next_) {}
    // void* operator new(unsigned,void* p){return p;}
} * e[M];

int aug(int no, int m) {
    if (no == n)
        return cost += pi1 * m, m;
    v[no] = true;
    int l = m;
    for (etype* i = e[no]; i; i = i->next)
        if (i->u && !i->c && !v[i->t]) {
            int d = aug(i->t, l < i->u ? l : i->u);
            i->u -= d, i->pair->u += d, l -= d;
            if (!l)
                return m;
        }
    return m - l;
}

bool modlabel() {
    int d = maxint;
    for (int i = 1; i <= n; ++i)
        if (v[i])
            for (etype* j = e[i]; j; j = j->next)
                if (j->u && !v[j->t] && j->c < d)
                    d = j->c;
    if (d == maxint)
        return false;
    for (int i = 1; i <= n; ++i)
        if (v[i])
            for (etype* j = e[i]; j; j = j->next)
                j->c -= d, j->pair->c += d;
    pi1 += d;
    return true;
}
int solve() {
    cost = 0;
    do
        do
            memset(v, 0, sizeof(v));
        while (aug(1, maxint));
    while (modlabel());
    return cost;
}
void addEdge(int s, int t, int u, int c) {
    e[s] = new etype(t, c, u, e[s]);
    e[t] = new etype(s, -c, 0, e[t]);
    e[s]->pair = e[t];
    e[t]->pair = e[s];
}
struct ED {
    int u, v, w;
    ED(int u = 0, int v = 0, int w = 0)
        : u(u)
        , v(v)
        , w(w) {}
};
struct PROBLEM {
    int n, m;
    int a[N][8];
    int b[N][8];
    int w[N];
    int v[N];
    vector<ED> g[N];
    void read() {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= 7; j++)
                scanf("%d", &a[i][j]);
            for (int j = 1; j <= 7; j++)
                scanf("%d", &b[i][j]);
            scanf("%d%d", &v[i], &w[i]);
        }
        for (int i = 1; i <= m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            g[u].push_back(ED(u, v, w));
            g[v].push_back(ED(v, u, w));
        }
    }

#define NODE(city, day) (((city - 1) * 7 + ((day) == 8 ? 1 : (day))) + 1)
#define FOR(i, s, t) for (int i = s; i <= t; i++)
    void solve() {
        //建图
        int s = 1;
        int t = n * 7 + 2;
        FOR(city, 1, n) {
            FOR(day, 1, 7) {
                // s->city(i,j) a[i][j] cost=0 产生的货物
                addEdge(s, NODE(city, day), a[city][day], 0);
                // city(i,j)->t b[i][j] cost=0 消耗的货物
                addEdge(NODE(city, day), t, b[city][day], 0);
            }
            //货物放到下一天
            FOR(day, 1, 7) addEdge(NODE(city, day), NODE(city, day + 1), v[city], w[city]);
            //货物运输到其他城市
            FOR(i, 0, g[city].size() - 1) {
                ED e = g[city][i];
                FOR(day, 1, 7) { addEdge(NODE(city, day), NODE(e.v, day), 0x7fff0000, e.w); }
            }
        }
    }
} problem;
int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    problem.read();
    problem.solve();
    n = problem.n * 7 + 2;
    printf("%d\n", solve());
    return 0;
}