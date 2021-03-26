#include <iostream>
#include <vector>
using namespace std;
// #define DEBUG

vector<int> arr;
int n, k;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        arr.push_back(i);
    int cur = 0, cnt = 1;
    while (arr.size() > 1) {
        if (cnt % k == 0 || cnt % 10 == k)
            arr.erase(arr.begin() + cur);
        else
            ++cur;
        if (cur >= arr.size())
            cur %= arr.size();
        ++cnt;
    }
    printf("%d", arr[0]);
    return 0;
}