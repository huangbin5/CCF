#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1005;
int arr[maxn], n, m;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        arr[i] = i;
    int p, q;
    while (m--) {
        scanf("%d%d", &p, &q);
        int idx;
        for (idx = 1; idx <= n; ++idx)
            if (arr[idx] == p)
                break;
        int i;
        if (q > 0) {
            for (i = idx + 1; i <= n && i <= idx + q; ++i)
                arr[i - 1] = arr[i];
            arr[i - 1] = p;
        } else {
            // q是负数，i >= idx + q
            for (i = idx - 1; i >= 0 && i >= idx + q; --i)
                arr[i + 1] = arr[i];
            arr[i + 1] = p;
        }
    }
    for (int i = 1; i <= n; ++i)
        if (i == 1)
            printf("%d", arr[i]);
        else
            printf(" %d", arr[i]);
    return 0;
}