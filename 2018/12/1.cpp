#include <iostream>
using namespace std;
#define DEBUG

const int maxn = 105;
int n, r, y, g, k, l;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &r, &y, &g, &n);
    int ans = 0;
    while (n--) {
        scanf("%d%d", &k, &l);
        switch (k) {
        case 2:
            ans += r;
        case 0:
        case 1:
            ans += l;
            break;
        default:
            break;
        }
    }
    printf("%d", ans);
    return 0;
}