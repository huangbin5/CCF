/**
 * 递归版本，因数据较大，爆栈了，80分
 * 其次，若用邻接矩阵，类型要是bool而不能为int，否则400M空间不够
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
// #define DEBUG

const int maxn = 10005;
struct Node {
    int v;
    bool del;
    Node(int _v)
        : v(_v) {
        del = false;
    }
    bool operator<(const Node tmp) const { return v < tmp.v; }
};
vector<Node> edge[maxn];
vector<int> path;
int n, m, oddNum = 0;
bool odd = false;

void dfs(int u) {
    for (int i = 0; i < edge[u].size(); ++i) {
        if (!edge[u][i].del) {
            int v = edge[u][i].v;
            //将相同的两条边删除
            edge[u][i].del = true;
            for (int j = 0; j < edge[v].size(); ++j) {
                if (u == edge[v][j].v)
                    edge[v][j].del = true;
            }
            dfs(v);
        }
    }
    path.push_back(u);
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(Node(v));
        edge[v].push_back(Node(u));
    }
    for (int i = 1; i <= n; ++i) {
        //判断是否存在欧拉路径
        if (edge[i].size() & 1) {
            if (i == 1)
                odd = true;
            else {
                ++oddNum;
                if (!odd || (odd && oddNum > 1)) {
                    printf("-1");
                    return 0;
                }
            }
        }
        //为了按字输出字典序最小的路径，给顶点的边先排序
        sort(edge[i].begin(), edge[i].end());
    }
    dfs(1);
    //容易漏掉：若路径顶点数太少，说明图不连通
    if (path.size() != m + 1) {
        printf("-1");
        return 0;
    }
    //路径是逆序存放的，倒着输出
    for (int i = path.size() - 1; i >= 0; --i) {
        if (i)
            printf("%d ", path[i]);
        else
            printf("%d", path[i]);
    }
    return 0;
}