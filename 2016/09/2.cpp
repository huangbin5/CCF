#include <iostream>
using namespace std;
// #define DEBUG

// rem-每排剩余票数
int tic[20][5] = { 0 }, rem[20];

//第r排分配num个座位
void allocate(int r, int& num) {
    for (int i = 0; i < 5 && num > 0; ++i)
        if (tic[r][i] == 0) {
            tic[r][i] = 1;
            printf("%d ", r * 5 + i + 1);
            --num;
            --rem[r];
        }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    for (int i = 0; i < 20; ++i)
        rem[i] = 5;
    int n, num;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &num);
        int i = 0;
        while (i < 20 && rem[i] < num)
            ++i;
        //没有相邻的
        if (i == 20) {
            i = 0;
            while (num > 0) {
                if (rem[i] > 0)
                    allocate(i, num);
                ++i;
            }
        } else
            allocate(i, num);
        puts("");
    }
    return 0;
}