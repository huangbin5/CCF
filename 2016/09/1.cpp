#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    int n, pre, cur, ans = 0;
    scanf("%d%d", &n, &pre);
    while (--n) {
        scanf("%d", &cur);
        ans = max(ans, abs(cur - pre));
        pre = cur;
    }
    printf("%d", ans);
    return 0;
}