#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1005;
int cake[maxn], n, k;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i)
        scanf("%d", &cake[i]);
    int sum = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        sum += cake[i];
        if (sum >= k) {
            ++ans;
            sum = 0;
        }
    }
    if (sum)
        ++ans;
    printf("%d", ans);
    return 0;
}