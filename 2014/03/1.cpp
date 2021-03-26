#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 505;
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
    int i = 0, j = n - 1, ans = 0;
    while (i < j) {
        if (a[i] > 0 || a[j] < 0)
            break;
        if (abs(a[i]) > a[j])
            ++i;
        else if (abs(a[i]) < a[j])
            --j;
        else {
            ++ans;
            ++i;
            --j;
        }
    }
    printf("%d", ans);
    return 0;
}