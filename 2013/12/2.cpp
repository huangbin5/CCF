#include <iostream>
using namespace std;
#define D1 (s[0] - '0') * 1
#define D2 (s[2] - '0') * 2
#define D3 (s[3] - '0') * 3
#define D4 (s[4] - '0') * 4
#define D5 (s[6] - '0') * 5
#define D6 (s[7] - '0') * 6
#define D7 (s[8] - '0') * 7
#define D8 (s[9] - '0') * 8
#define D9 (s[10] - '0') * 9
#define D10 (s[12] - '0')
// #define DEBUG

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    char s[15];
    scanf("%s", s);
    int code = (D1 + D2 + D3 + D4 + D5 + D6 + D7 + D8 + D9) % 11;
    if (code == D10 || (code == 10 && s[12] == 'X'))
        printf("Right");
    else {
        s[12] = code == 10 ? 'X' : code + '0';
        printf("%s", s);
    }
    return 0;
}