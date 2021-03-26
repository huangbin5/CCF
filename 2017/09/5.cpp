/**
 * 能省时间的地方尽量省时间
 */
#include <iostream>
using namespace std;
// #define DEBUG

typedef long long ll;
#define lowbit(x) ((x) & (-(x)))
const int maxn = 100005;
// a-原始数组，c-树状数组
int a[maxn] = { 0 }, n, m;
//应该用long long，否则会超时得30分（按理应该是答案错误啊，不知道为什么是超时）
ll c[maxn] = { 0 };

ll getSum(int x) {
    ll sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        sum += c[i];
    return sum;
}

void add(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += v;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        add(i, a[i]);
    }
    int t, l, r, v;
    while (m--) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d%d", &l, &r, &v);
            // v为1时结果不变，加上此句可由50分变为80分
            if (v == 1)
                continue;
            for (int i = l; i <= r; ++i) {
                //加上a[i] >= v可由80分变为100分？是因为求模运算很慢吗？
                if (a[i] >= v && a[i] % v == 0) {
                    add(i, a[i] / v - a[i]);
                    a[i] /= v;
                }
            }
        } else {
            scanf("%d%d", &l, &r);
            printf("%lld\n", getSum(r) - getSum(l - 1));
        }
    }
    return 0;
}
