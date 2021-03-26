#include <iostream>
#include <vector>
using namespace std;
// #define DEBUG

const int maxn = 10005;
struct Node {
    char sr;
    int id;
    Node() {}
    Node(char _sr, int _id)
        : sr(_sr)
        , id(_id) {}
};
vector<Node> node[maxn];
int send[maxn], recv[maxn];
int pos[maxn];
int T, N;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &T, &N);
    getchar();
    char sr, sp;
    int id;
    while (T--) {
        //初始化
        for (int i = 0; i < N; ++i) {
            node[i].clear();
            send[i] = -1;
            recv[i] = -1;
            pos[i] = 0;
        }
        //输入
        /**
         * 这种输入处理方式还不太熟悉，花了比较多时间
         */
        for (int i = 0; i < N; ++i) {
            for (;;) {
                if (scanf("%c%d%c", &sr, &id, &sp) != EOF) {
                    node[i].push_back(Node(sr, id));
                    if (sp == '\n' || sp == EOF)
                        break;
                } else
                    break;
            }
        }
        bool change;
        //不断地循环遍历每个进程
        for (;;) {
            //判断这次循环是否做了改变
            change = false;
            //对于每个进程
            for (int i = 0; i < N; ++i) {
                while (pos[i] < node[i].size()) {
                    if (send[i] != -1 || recv[i] != -1)
                        break;
                    change = true;
                    Node tmp = node[i][pos[i]];
                    ++pos[i];
                    if (tmp.sr == 'S') {
                        //发送
                        if (recv[tmp.id] == i)
                            //匹配
                            recv[tmp.id] = -1;
                        else
                            //暂未匹配，加入发送队列
                            send[i] = tmp.id;
                    } else {
                        //接收
                        if (send[tmp.id] == i)
                            //匹配
                            send[tmp.id] = -1;
                        else
                            //暂未匹配，加入接收队列
                            recv[i] = tmp.id;
                    }
                }
            }
            //如果这次循环没有发生任何变化，则检查是否合法结束了
            if (!change) {
                for (int i = 0; i < N; ++i) {
                    //该进程没有结束
                    if (send[i] != -1 || recv[i] != -1 || pos[i] < node[i].size()) {
                        printf("1\n");
                        change = true;
                        break;
                    }
                }
                if (!change)
                    printf("0\n");
                break;
            }
        }
    }
    return 0;
}