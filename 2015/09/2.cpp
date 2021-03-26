#include <iostream>
using namespace std;
// #define DEBUG

int days[][2] = { { 0, 0 }, { 31, 31 }, { 28, 29 }, { 31, 31 }, { 30, 30 }, { 31, 31 }, { 30, 30 }, { 31, 31 }, { 31, 31 },
    { 30, 30 }, { 31, 31 }, { 30, 30 }, { 31, 31 } };

int isRun(int x) {
    if (x % 400 == 0 || (x % 4 == 0 && x % 100 != 0))
        return 1;
    return 0;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    int year, num;
    scanf("%d%d", &year, &num);
    int total = 0, run = isRun(year), month;
    for (month = 1; month <= 12; ++month) {
        if (total + days[month][run] >= num)
            break;
        total += days[month][run];
    }
    printf("%d\n%d", month, num - total);
    return 0;
}