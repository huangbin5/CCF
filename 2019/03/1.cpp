#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 100005;
int arr[maxn], n;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[i]);
    int b;
    int a = max(arr[0], arr[n - 1]);
    int c = min(arr[0], arr[n - 1]);
    if (n % 2) {
        b = arr[n / 2];
        printf("%d %d %d", a, b, c);
    } else {
        int tmp = arr[n / 2] + arr[n / 2 - 1];
        b = tmp / 2;
        if (tmp % 2)
            printf("%d %d.5 %d", a, b, c);
        else
            printf("%d %d %d", a, b, c);
    }
    return 0;
}