#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 305;
int fir[maxn], sec[maxn], n;
//当前摊位编号，前一个摊位价格，前两个摊位价格，若为true则说明之前出现过被排除了
/**
 * 没有这个记忆化会超时
 */
bool dp[maxn][maxn][maxn] = { false };

bool dfs(int cur) {
    //递归基
    if (cur == n - 1) {
        //对于n-2号，3*sec[cur-1] <= fir[cur-2]+fir[cur-1]+fir[cur] <= 3*sec[cur-1]+2
        //对于n-1号，2*sec[cur] <= fir[cur-1]+fir[cur] <= 2*sec[cur]+1
        fir[cur] = max(3 * sec[cur - 1] - fir[cur - 2] - fir[cur - 1], 2 * sec[cur] - fir[cur - 1]);
        //做上界判断
        if (fir[cur - 2] + fir[cur - 1] + fir[cur] <= 3 * sec[cur - 1] + 2 && fir[cur - 1] + fir[cur] <= 2 * sec[cur] + 1)
            return true;
        return false;
    }
    if (cur == 0) {
        //对于0号，2*sec[cur] <= fir[cur]+fir[cur+1] <= 2*sec[cur]+1
        //由于fir[cur+1] >= 1，故fir[cur] <= 2*sec[cur]
        for (int i = 1; i <= 2 * sec[cur]; ++i) {
            fir[cur] = i;
            if (dfs(cur + 1))
                return true;
        }
    } else if (cur == 1) {
        //对于0号，2*sec[cur-1] <= fir[cur-1]+fir[cur] <= 2*sec[cur-1]+1
        //对于1号，3*sec[cur] <= fir[cur-1]+fir[cur]+fir[cur+1] <= 3*sec[cur]+2
        //由于fir[cur+1] >= 1，故fir[cur-1]+fir[cur] <= 3*sec[cur]+1
        int start = max(1, 2 * sec[cur - 1] - fir[cur - 1]);
        int end1 = 2 * sec[cur - 1] + 1 - fir[cur - 1];
        int end2 = 3 * sec[cur] + 1 - fir[cur - 1];
        for (int i = start; i <= end1 && i <= end2; ++i) {
            fir[cur] = i;
            if (dfs(cur + 1))
                return true;
        }
    } else {
        //对于cur-1号，3*sec[cur-1] <= fir[cur-2]+fir[cur-1]+fir[cur] <= 3*sec[cur-1]+2
        //对于cur号，3*sec[cur] <= fir[cur-1]+fir[cur]+fir[cur+1] <= 3*sec[cur]+2
        //由于fir[cur+1] >= 1，故fir[cur-1]+fir[cur] <= 3*sec[cur]+1
        int start = max(1, 3 * sec[cur - 1] - fir[cur - 2] - fir[cur - 1]);
        int end1 = 3 * sec[cur - 1] + 2 - fir[cur - 2] - fir[cur - 1];
        int end2 = 3 * sec[cur] + 1 - fir[cur - 1];
        //之前出现过，直接返回false
        if (dp[cur][fir[cur - 1]][fir[cur - 2]])
            return false;
        for (int i = start; i <= end1 && i <= end2; ++i) {
            fir[cur] = i;
            if (dfs(cur + 1))
                return true;
        }
        //标记为出现过
        dp[cur][fir[cur - 1]][fir[cur - 2]] = true;
    }
    return false;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &sec[i]);
    dfs(0);
    for (int i = 0; i < n - 1; ++i)
        printf("%d ", fir[i]);
    printf("%d", fir[n - 1]);
    return 0;
}