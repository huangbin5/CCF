#include <iostream>
using namespace std;
// #define DEBUG

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    char c;
    int ans = 0;
    while (scanf("%c", &c) != EOF) {
        if (c >= '0' && c <= '9')
            ans += c - '0';
    }
    printf("%d", ans);
    return 0;
}