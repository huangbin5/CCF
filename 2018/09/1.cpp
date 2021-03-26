#include <iostream>
using namespace std;
// #define DEBUG

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    const int maxn = 1005;
    int n, a[maxn];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    printf("%d ", (a[0] + a[1]) / 2);
    for (int i = 1; i < n - 1; ++i)
        printf("%d ", (a[i - 1] + a[i] + a[i + 1]) / 3);
    printf("%d", (a[n - 2] + a[n - 1]) / 2);
    return 0;
}