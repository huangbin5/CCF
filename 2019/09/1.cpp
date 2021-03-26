// INFO BEGIN
//
// User = 201910012657(黄斌)
// Group = C/C++
// Problem = 小明种苹果
// Language = CPP11
// SubmitTime = 2019-09-15 13:48:09
//
// INFO END

#include <algorithm>
#include <cstdio>
#include <iostream>
typedef long long ll;
using namespace std;
// #define DEBUG

const int maxn = 1005;
int origin[maxn], change[maxn] = { 0 };
int n, m, maxId, maxChange = 0, sumOri = 0, sumChan = 0;

int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif // DEBUG
    scanf("%d%d", &n, &m);
    int a;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &origin[i]);
        sumOri += origin[i];
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a);
            change[i] += a;
        }
        sumChan += change[i];
        if (change[i] < maxChange) {
            maxChange = change[i];
            maxId = i;
        }
    }
    printf("%d %d %d", sumOri + sumChan, maxId, -maxChange);
    return 0;
}
