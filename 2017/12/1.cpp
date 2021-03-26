#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1005;
int arr[maxn], n;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[i]);
    sort(arr, arr + n);
    int ans = 10005, tmp;
    for (int i = 1; i < n; ++i) {
        tmp = abs(arr[i] - arr[i - 1]);
        if (tmp < ans)
            ans = tmp;
    }
    printf("%d", ans);
    return 0;
}