#include <iostream>
using namespace std;
// #define DEBUG

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    int a, ans = 0, now = 0;
    while (scanf("%d", &a) && a) {
        if (a == 1) {
            now = 0;
            ++ans;
        } else {
            now += 2;
            ans += now;
        }
    }
    printf("%d", ans);
    return 0;
}