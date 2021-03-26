#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 100005;
const ll MOD = 1000000000000000000;
struct City {
    ll pre, dis, v, f;
    City() {}
    City(ll _pre, ll _dis, ll _v, ll _f)
        : pre(_pre)
        , dis(_dis)
        , v(_v)
        , f(_f) {}
} city[maxn];
ll value[maxn];
int T, n;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld%lld%lld%lld", &city[i].pre, &city[i].dis, &city[i].v, &city[i].f);
            value[i] = 0;
        }
        for (int i = n; i > 0; --i) {
            ll cur = city[i].pre;
            ll curDis = city[i].dis;
            while (cur > 0) {
                ll tmpValue = city[cur].f - curDis;
                tmpValue = value[i] + city[cur].v - tmpValue * tmpValue;
                if (tmpValue > value[cur])
                    value[cur] = tmpValue;
                curDis += city[cur].dis;
                //后更新cur
                cur = city[cur].pre;
            }
        }
        ll ans = 0;
        for (int i = 1; i <= n; ++i) {
            // printf("%02d: %lld\n", i, value[i]);
            ans = (ans + value[i]) % MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}