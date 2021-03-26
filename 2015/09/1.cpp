#include <iostream>
using namespace std;
// #define DEBUG

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    int n, cur, pre, ans = 0;
    scanf("%d%d", &n, &pre);
    while (--n) {
        scanf("%d", &cur);
        if (cur != pre) {
            ++ans;
            pre = cur;
        }
    }
    printf("%d", ans + 1);
    return 0;
}