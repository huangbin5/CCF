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
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    int ans = 0;
    for (int i = 1; i < n - 1; ++i) {
        if (!((arr[i - 1] < arr[i]) ^ (arr[i] > arr[i + 1])))
            ++ans;
    }
    printf("%d", ans);
    return 0;
}