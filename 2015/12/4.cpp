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
stack<pair<int, int>> s;

/**
 * 将尾递归改为迭代版本，用自己建的栈就不会爆了
 */
void dfs(int x) {
    //栈顶节点编号以及下一个该遍历的邻居下标
    s.push(make_pair(x, 0));
    while (!s.empty()) {
        int u = s.top().first, i = s.top().second;
        while (i < edge[u].size() && edge[u][i].del)
            ++i;
        if (i < edge[u].size()) {
            int v = edge[u][i].v;
            edge[u][i].del = true;
            for (int j = 0; j < edge[v].size(); ++j) {
                if (u == edge[v][j].v)
                    edge[v][j].del = true;
            }
            s.top().second = i + 1;
            s.push(make_pair(v, 0));
        } else {
            path.push_back(u);
            s.pop();
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