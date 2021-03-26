/**
 * 当开盘价低了：买股就多，卖股就少
 * 当开盘价高了：买股就少，卖股就多
 * 成交量随着开盘价升高先是升高然后降低
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
#define DEBUG

const int maxn = 5005;
struct Node {
    // 0-取消；1-买；2-卖
    int type, num;
    double price;
    bool valid;
    Node() {}
    Node(int _type, bool _valid, double _price = 0, int _num = 0)
        : type(_type)
        , valid(_valid)
        , price(_price)
        , num(_num) {}
} node[maxn];
vector<Node> buy, sell;
double prices[maxn];
int nSize = 1, pSize = 0;
ll buyAmount, sellAmount, maxAmount = 0;

//计算成交量
void cacul(int x) {
    buyAmount = 0, sellAmount = 0;
    for (int i = 0; i < buy.size(); ++i) {
        if (buy[i].price >= prices[x])
            buyAmount += buy[i].num;
    }
    for (int i = 0; i < sell.size(); ++i) {
        if (sell[i].price <= prices[x])
            sellAmount += sell[i].num;
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    char type[10];
    double price;
    int num;
    while (scanf("%s", type) != EOF) {
        if (type[0] == 'b') {
            scanf("%lf%d", &price, &num);
            node[nSize++] = Node(1, true, price, num);
        } else if (type[0] == 's') {
            scanf("%lf%d", &price, &num);
            node[nSize++] = Node(2, true, price, num);
        } else {
            scanf("%d", &num);
            node[num].valid = false;
            node[nSize++] = Node(0, false);
        }
    }
    for (int i = 1; i <= nSize; ++i) {
        if (node[i].valid) {
            if (node[i].type == 1) {
                buy.push_back(node[i]);
            } else {
                sell.push_back(node[i]);
            }
            prices[pSize++] = node[i].price;
        }
    }
    sort(prices, prices + pSize);
    //寻找成交量升高后降低的转折点
    int idx = 0;
    while (idx < pSize) {
        cacul(idx);
        if (min(buyAmount, sellAmount) >= maxAmount) {
            maxAmount = min(buyAmount, sellAmount);
            ++idx;
        } else
            break;
    }
    printf("%.2f %lld", prices[idx - 1], maxAmount);
    return 0;
}