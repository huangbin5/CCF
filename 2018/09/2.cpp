#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1000005;
bool h[maxn] = { false };
int n;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    int a, b;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a, &b);
        for (int j = a; j < b; ++j)
            h[j] = true;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a, &b);
        for (int j = a; j < b; ++j)
            if (h[j])
                ++ans;
    }
    printf("%d", ans);
    return 0;
}