#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1005;
int num[maxn], n;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &num[i]);
    sort(num, num + n);
    int right = n >> 1, left = right, ans = num[right];
    if (n % 2 == 0)
        --left;
    while (left >= 0 && right < n && num[left] == ans && num[right] == ans) {
        --left;
        ++right;
    }
    if ((left < 0 && right >= n) || (num[left] != ans && num[right] != ans))
        printf("%d", ans);
    else
        printf("-1");
    return 0;
}