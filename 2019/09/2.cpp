// INFO BEGIN
//
// User = 201910012657(黄斌)
// Group = C/C++
// Problem = 小明种苹果（续）
// Language = CPP11
// SubmitTime = 2019-09-15 14:10:07
//
// INFO END

#include <cstdio>
#include <iostream>
typedef long long ll;
using namespace std;
//#define DEBUG

const int maxn = 1005;
int sum[maxn] = { 0 };
bool isFall[maxn] = { false };
int n, sumAns = 0, fallAns = 0, pairAns = 0;

int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    scanf("%d", &n);
    int m, a;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &m);
        for (int j = 0; j < m; ++j) {
            scanf("%d", &a);
            //统计总数
            if (a > 0) {
                if (sum[i] > a) {
                    isFall[i] = true;
                }
                sum[i] = a;
            } else {
                //蔬果
                sum[i] += a;
            }
        }
        sumAns += sum[i];
    }
    for (int i = 1; i <= n; ++i) {
        if (isFall[i]) {
            ++fallAns;
            if (isFall[i % n + 1] && isFall[(i + 1) % n + 1])
                ++pairAns;
        }
    }
    printf("%d %d %d", sumAns, fallAns, pairAns);
    return 0;
}
