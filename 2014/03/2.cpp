#include <iostream>
#include <vector>
using namespace std;
// #define DEBUG

struct Window {
    int x1, y1, x2, y2;
    int id;
    Window() {}
    Window(int _x1, int _y1, int _x2, int _y2, int _id)
        : x1(_x1)
        , y1(_y1)
        , x2(_x2)
        , y2(_y2)
        , id(_id) {}
    bool contain(int x, int y) {
        if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
            return true;
        return false;
    }
};
vector<Window> wins;
int n, m;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    int x1, y1, x2, y2, x, y;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        wins.push_back(Window(x1, y1, x2, y2, i));
    }
    while (m--) {
        scanf("%d%d", &x, &y);
        int i;
        for (i = n - 1; i >= 0; --i) {
            if (wins[i].contain(x, y)) {
                Window tmp = wins[i];
                printf("%d\n", tmp.id);
                wins.erase(wins.begin() + i);
                wins.push_back(tmp);
                break;
            }
        }
        if (i < 0)
            printf("IGNORED\n");
    }
    return 0;
}