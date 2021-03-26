#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1005;
int a[maxn], n;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    sort(a, a + n);
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] - a[i - 1] == 1)
            ++ans;
    }
    printf("%d", ans);
    return 0;
}