#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
// #define DEBUG

const int maxn = 1005;
struct Node {
    //钥匙编号，借还时间，类型0-借 1-还
    int id, time, type;
    Node() {}
    Node(int _id, int _time, int _type)
        : id(_id)
        , time(_time)
        , type(_type) {}
};
vector<Node> keys;
int box[maxn];
int n, k;

bool cmp(Node& a, Node& b) {
    //先按时间排序
    if (a.time != b.time)
        return a.time < b.time;
    //时间相同先还后借
    if (a.type != b.type)
        return a.type > b.type;
    //同时还按编号由小到大
    return a.id < b.id;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    //输入n之后再初始化
    for (int i = 1; i <= n; ++i)
        box[i] = i;
    int id, t1, t2;
    while (k--) {
        scanf("%d%d%d", &id, &t1, &t2);
        keys.push_back(Node(id, t1, 0));
        keys.push_back(Node(id, t1 + t2, 1));
    }
    sort(keys.begin(), keys.end(), cmp);
    for (int j = 0; j < keys.size(); ++j) {
        Node& nd = keys[j];
        if (nd.type == 0) {
            //借
            for (int i = 1; i <= n; ++i) {
                if (box[i] == nd.id) {
                    box[i] = 0;
                    break;
                }
            }
        } else {
            //还
            for (int i = 1; i <= n; ++i) {
                if (box[i] == 0) {
                    box[i] = nd.id;
                    break;
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (i == 1)
            printf("%d", box[i]);
        else
            printf(" %d", box[i]);
    }
    return 0;
}