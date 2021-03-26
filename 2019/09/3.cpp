// INFO BEGIN
//
// User = 201910012657(黄斌)
// Group = C/C++
// Problem = 字符画
// Language = CPP11
// SubmitTime = 2019-09-15 15:40:56
//
// INFO END

/**
 * 【input】
 * 2 1
 * 2 1
 * #654321
 * #fedcba
 * 【output】
 * \x1B\x5B\x34\x38\x3B\x32\x3B\x31\x37\x37\x3B\x31\x34\x33\x3B\x31\x30\x39\x6D\x20\x1B\x5B\x30\x6D\x0A
 */

#include <cstdio>
#include <cstring>
#include <iostream>
typedef long long ll;
using namespace std;

const int maxn = 1100, maxm = 2000;
struct Color {
    int r, g, b;
} color[maxn][maxm];
int n, m, p, q;
char s[10];
int pr = 0, pg = 0, pb = 0;

int to_dec(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    return c - 'a' + 10;
}

void input(int i, int j) {
    scanf("%s", s);
    int len = strlen(s);
    if (len == 7) {
        color[i][j].r = (to_dec(s[1]) * 16 + to_dec(s[2]));
        color[i][j].g = (to_dec(s[3]) * 16 + to_dec(s[4]));
        color[i][j].b = (to_dec(s[5]) * 16 + to_dec(s[6]));
    } else if (len == 4) {
        color[i][j].r = (to_dec(s[1]) * 16 + to_dec(s[1]));
        color[i][j].g = (to_dec(s[2]) * 16 + to_dec(s[2]));
        color[i][j].b = (to_dec(s[3]) * 16 + to_dec(s[3]));
    } else {
        color[i][j].r = (to_dec(s[1]) * 16 + to_dec(s[1]));
        color[i][j].g = (to_dec(s[1]) * 16 + to_dec(s[1]));
        color[i][j].b = (to_dec(s[1]) * 16 + to_dec(s[1]));
    }
}

void printInt(int a) {
    string tmp = to_string(a);
    for (auto c : tmp)
        printf("\\x%X", c);
}

void setColor(int r, int g, int b) {
    printf("\\x1B\\x5B\\x34\\x38\\x3B\\x32\\x3B");
    printInt(r);
    printf("\\x3B");
    printInt(g);
    printf("\\x3B");
    printInt(b);
    printf("\\x6D");
}

void setDefault() { printf("\\x1B\\x5B\\x30\\x6D"); }

void printBlank() { printf("\\x20"); }

void printLine() { printf("\\x0A"); }

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    scanf("%d%d%d%d", &m, &n, &p, &q);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            // 输入每个像素
            input(i, j);
    for (int i = 0; i < n / q; ++i) {
        for (int j = 0; j < m / p; ++j) {
            int r = 0, g = 0, b = 0;
            for (int x = i * q; x < i * q + q; ++x)
                for (int y = j * p; y < j * p + p; ++y)
                    // 每一小块的总和
                    r += color[x][y].r, g += color[x][y].g, b += color[x][y].b;
            // 每一小块的平均值
            r /= p * q, g /= p * q, b /= p * q;
            // 颜色改变了
            if (r != pr || g != pg || b != pb) {
                // 设置新的颜色
                r + g + b ? setColor(r, g, b) : setDefault();
                pr = r, pg = g, pb = b;
            }
            // 空白字符，会显示背景色
            printBlank();
        }
        // 重置颜色
        if (pr != 0 || pg != 0 || pb != 0) {
            setDefault();
            pr = 0, pg = 0, pb = 0;
        }
        // 换行
        printLine();
    }
    return 0;
}
