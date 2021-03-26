#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 100005;
int n, r, y, g, k, t;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &r, &y, &g, &n);
    /**
     * 要用long long类型，否则只有60分
     * 看题目特地在10^3后面说明10^5的用例就要想到要用long long类型
     */
    ll ans = 0, yrg = y + r + g;
    while (n--) {
        scanf("%d%d", &k, &t);
        //按黄红绿循环，[0, y+r)为不能通过，[y+r, y+r+g)为可以通过
        if (k == 0)
            ans += t;
        else {
            if (k == 1)
                t = (r - t + y + ans) % yrg;
            else if (k == 2)
                t = (y - t + ans) % yrg;
            else
                t = (g - t + y + r + ans) % yrg;
            if (t < y + r)
                ans += y + r - t;
        }
    }
    printf("%lld", ans);
    return 0;
}