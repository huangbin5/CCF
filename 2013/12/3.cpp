#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1005;
int hei[maxn], n, maxArea = 0;

int getMax(int lo, int hi) {
    //寻找最矮的下标
    int lowest = lo;
    for (int i = lo + 1; i <= hi; ++i) {
        if (hei[i] < hei[lowest]) {
            lowest = i;
        }
    }
    //最大值要么是在lowest左边，要么在lowest右边，要么横跨lowest
    int ans = hei[lowest] * (hi - lo + 1);
    if (lowest - 1 >= lo) {
        int maxLeft = getMax(lo, lowest - 1);
        if (maxLeft > ans)
            ans = maxLeft;
    }
    if (lowest + 1 <= hi) {
        int maxRight = getMax(lowest + 1, hi);
        if (maxRight > ans)
            ans = maxRight;
    }
    return ans;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &hei[i]);
    }
    printf("%d", getMax(0, n - 1));
    return 0;
}