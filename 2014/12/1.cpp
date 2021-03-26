#include <iostream>
using namespace std;
#define DEBUG

const int maxn = 1005;
int cnt[maxn] = { 0 }, n;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    int num;
    while (n--) {
        scanf("%d", &num);
        ++cnt[num];
        if (n)
            printf("%d ", cnt[num]);
        else
            printf("%d\n", cnt[num]);
    }
    return 0;
}