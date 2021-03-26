#include <iostream>
#include <string>
using namespace std;
// #define DEBUG

const int maxn = 1005;
int n, s, m, k;
string line[maxn];
char orz[16][16];

int hexToDec(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    return c - 'A' + 10;
}

char decToHex(int a) {
    if (a >= 0 && a <= 9)
        return a + '0';
    return a - 10 + 'A';
}

void init() {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            orz[i][j] = decToHex(i ^ j);
        }
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    /**
     * 不加这个输入不管怎样都会超时
     */
    ios::sync_with_stdio(false);
    init();
    cin >> n >> s >> m;
    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> b;
        cin >> line[b];
    }
    int total = (n - 1) * line[b].size() / 8;
    cin >> k;
    int block, stripe, row, check, disk, inBlock, pos;
    for (int i = 0; i < k; ++i) {
        cin >> block;
        if (block < total) {
            stripe = block / s;
            row = stripe / (n - 1);
            check = n - 1 - row % n;
            disk = (check + 1 + stripe % (n - 1)) % n;
            inBlock = block % s;
            pos = (row * s + inBlock) * 8;
            if (!line[disk].empty()) {
                cout << line[disk].substr(pos, 8) << endl;
            } else if (m == n - 1) {
                string ans(8, '0');
                for (int l = 0; l < n; ++l) {
                    if (l != disk) {
                        for (int j = 0; j < 8; ++j) {
                            ans[j] = orz[hexToDec(ans[j])][hexToDec(line[l][pos + j])];
                        }
                    }
                }
                cout << ans << endl;
            } else {
                cout << "-\n";
            }
        } else {
            cout << "-\n";
        }
    }
    return 0;
}