/**
 * 不能直接用Dijkstra算法的原因是局部的最短路并不是全局的最短路，当连续走小路时后面疲劳值会暴增
 * 先将所有顶点之间只通过小路连通的距离算出来，然后在讨论的时候不能连续走小路，就可以用spfa求出最短路径
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 505;
const int INF = 0x3f3f3f3f;
//不明白两个顶点之间的距离为什么也要用long long类型
//按题目的数据范围最大应该是(500 - 1) * 10 ^ 5，并没有超过INF
//后两题尽量还是用long long，空间256M远远足够
ll bigG[maxn][maxn], smallG[maxn][maxn];
ll bigFat[maxn], smallFat[maxn];
bool inq[maxn] = { false };
int n, m;

void init() {
    memset(bigG, INF, sizeof(bigG));
    memset(smallG, INF, sizeof(smallG));
    memset(bigFat, INF, sizeof(bigFat));
    memset(smallFat, INF, sizeof(smallFat));
}

void floyd() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                //加上判断是否等于INF会超时
                if (smallG[i][k] + smallG[k][j] < smallG[i][j])
                    smallG[i][j] = smallG[i][k] + smallG[k][j];
            }
        }
    }
}

void spfa() {
    bigFat[1] = smallFat[1] = 0;
    queue<int> q;
    q.push(1);
    inq[1] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v = 1; v <= n; ++v) {
            //这一段路是大路，上一段路也是大路
            if (bigFat[u] + bigG[u][v] < bigFat[v]) {
                bigFat[v] = bigFat[u] + bigG[u][v];
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
            //这一段路是大路，上一段路是小路
            if (smallFat[u] + bigG[u][v] < bigFat[v]) {
                bigFat[v] = smallFat[u] + bigG[u][v];
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
            //这一段是小路，上一段一定要是大路
            //写smallG[u][v] != INF会扣分，莫名其妙
            //加小于判断主要是因为平方后可能溢出，但按题目数据范围n-1条边之和也不会超过INF
            if (smallG[u][v] < INF) {
                ll tmp = smallG[u][v] * smallG[u][v];
                if (bigFat[u] + tmp < smallFat[v]) {
                    smallFat[v] = bigFat[u] + tmp;
                    if (!inq[v]) {
                        q.push(v);
                        inq[v] = true;
                    }
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
    init();
    scanf("%d%d", &n, &m);
    int t, u, v, d;
    while (m--) {
        scanf("%d%d%d%d", &t, &u, &v, &d);
        //两个顶点之间可能会有多条边，取最小的
        if (t == 0 && bigG[u][v] > d)
            bigG[u][v] = bigG[v][u] = d;
        else if (t == 1 && smallG[u][v] > d)
            smallG[u][v] = smallG[v][u] = d;
    }
    floyd();
    spfa();
    printf("%d", min(bigFat[n], smallFat[n]));
    return 0;
}