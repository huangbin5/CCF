#include <cmath>
#include <iostream>
using namespace std;
// #define DEBUG

int pre[8] = { 3500, 5000, 8000, 12500, 38500, 58500, 83500, 100000 };
int post[8] = { 3500 };
double rate[8] = { 0, 0.03, 0.1, 0.2, 0.25, 0.3, 0.35, 0.45 };

void init() {
    int tax = 0;
    for (int i = 1; i < 8; ++i) {
        tax += (pre[i] - pre[i - 1]) * rate[i];
        post[i] = pre[i] - tax;
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    init();
    int n;
    scanf("%d", &n);
    int i = 1;
    while (n > post[i])
        ++i;
    //因为结果是整百
    int ans = round((pre[i - 1] + (n - post[i - 1]) / (1 - rate[i])) / 100) * 100;
    printf("%d", ans);
    return 0;
}