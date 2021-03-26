#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1005;
struct Node {
    int v, cnt;
    Node() { cnt = 0; }
} node[maxn];
int n;

bool cmp(Node a, Node b) {
    if (a.cnt != b.cnt)
        return a.cnt > b.cnt;
    return a.v < b.v;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    for (int i = 0; i < maxn; ++i) {
        node[i].v = i;
    }
    scanf("%d", &n);
    int a;
    while (n--) {
        scanf("%d", &a);
        ++node[a].cnt;
    }
    sort(node, node + maxn, cmp);
    for (int i = 0; i < maxn; ++i) {
        if (node[i].cnt == 0)
            break;
        printf("%d %d\n", node[i].v, node[i].cnt);
    }
    return 0;
}