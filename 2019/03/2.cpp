#include <iostream>
using namespace std;
// #define DEBUG

int dig[5], optN;
char opt[5];

void move(int idx, int num) {
    dig[idx] = num;
    for (int i = idx + 1; i < optN; ++i) {
        dig[i] = dig[i + 1];
        opt[i - 1] = opt[i];
    }
    --optN;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    while (n--) {
        scanf("%d%c%d%c%d%c%d", &dig[0], &opt[0], &dig[1], &opt[1], &dig[2], &opt[2], &dig[3]);
        optN = 3;
        for (int i = 0; i < optN;) {
            if (opt[i] == 'x')
                move(i, dig[i] * dig[i + 1]);
            else if (opt[i] == '/')
                move(i, dig[i] / dig[i + 1]);
            else
                ++i;
        }
        while (optN) {
            if (opt[0] == '+')
                move(0, dig[0] + dig[1]);
            else
                move(0, dig[0] - dig[1]);
        }
        if (dig[0] == 24)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}