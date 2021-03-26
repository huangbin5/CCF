#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 105;
struct Ball {
    int id, pos, dir;
    Ball() {}
    Ball(int _id, int _dir)
        : id(_id)
        , dir(_dir) {}
} ball[maxn];
int n, l, t;

bool cmpPos(Ball& a, Ball& b) { return a.pos < b.pos; }

bool cmpId(Ball& a, Ball& b) { return a.id < b.id; }

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &l, &t);
    for (int i = 1; i <= n; ++i) {
        ball[i] = Ball(i, 1);
        scanf("%d", &ball[i].pos);
    }
    sort(ball + 1, ball + n + 1, cmpPos);
    while (t--) {
        for (int i = 1; i <= n; ++i) {
            ball[i].pos += ball[i].dir;
        }
        if (ball[1].pos == 0 && ball[1].dir == -1)
            ball[1].dir = 1;
        if (ball[n].pos == l && ball[n].dir == 1)
            ball[n].dir = -1;
        for (int i = 1; i < n; ++i) {
            if (ball[i].pos == ball[i + 1].pos && ball[i].dir == 1 && ball[i + 1].dir == -1) {
                ball[i].dir = -1;
                ball[i + 1].dir = 1;
            }
        }
    }
    sort(ball + 1, ball + n + 1, cmpId);
    for (int i = 1; i <= n; ++i) {
        if (i == 1)
            printf("%d", ball[i].pos);
        else
            printf(" %d", ball[i].pos);
    }
    return 0;
}