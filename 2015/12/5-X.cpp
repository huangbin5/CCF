#include <ctime>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxm = 1005;
typedef bool matrix[maxm][maxm];
typedef bool colVec[maxm];
matrix A, Ak;
colVec b, Akb;
int m, n, r;

void init(matrix& p1, matrix& p2) {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j)
            if (i == j)
                p1[i][j] = 1;
            else
                p1[i][j] = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j)
            p2[i][j] = A[i][j];
}

void nx1(matrix& p1, colVec& p2) {
    for (int i = 0; i < m; ++i)
        Akb[i] = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j)
            Akb[i] ^= (p1[i][j] & p2[j]);
}

void nxn(matrix& p1, matrix& p2) {
    matrix tmpA;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j)
            tmpA[i][j] = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < m; ++k)
                tmpA[i][j] = tmpA[i][j] ^ (p1[i][k] & p2[k][j]);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j)
            p1[i][j] = tmpA[i][j];
}

//矩阵快速幂
void quickPow(int x) {
    matrix Ap;
    init(Ak, Ap);
    while (x) {
        if (x & 1)
            nxn(Ak, Ap);
        nxn(Ap, Ap);
        x >>= 1;
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &m);
    char c;
    for (int i = 0; i < m; ++i) {
        getchar();
        for (int j = 0; j < m; ++j) {
            scanf("%c", &c);
            A[i][j] = c - '0';
        }
    }
    getchar();
    for (int i = 0; i < m; ++i) {
        scanf("%c", &c);
        b[i] = c - '0';
    }
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &r);
        quickPow(r);
        nx1(Ak, b);
        for (int i = 0; i < m; ++i)
            printf("%d", Akb[i]);
        puts("");
    }
    return 0;
}