#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 10005;
int arr[maxn] = { 0 };

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    int n, tmp, maxCnt = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &tmp);
        arr[tmp]++;
        if (arr[tmp] > maxCnt)
            maxCnt = arr[tmp];
    }
    for (int i = 0; i < maxn; ++i) {
        if (arr[i] == maxCnt) {
            printf("%d\n", i);
            return 0;
        }
    }
    return 0;
}