#include <iostream>
using namespace std;
// #define DEBUG

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    int n, ans = 0;
    scanf("%d", &n);
    while (n >= 50) {
        ans += 7;
        n -= 50;
    }
    while (n >= 30) {
        ans += 4;
        n -= 30;
    }
    while (n > 0) {
        ++ans;
        n -= 10;
    }
    printf("%d", ans);
    return 0;
}