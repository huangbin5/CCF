#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 45;
struct Task {
    int c, cg, cc;
    Task() {}
    Task(int _c, int _cg, int _cc)
        : c(_c)
        , cg(_cg)
        , cc(_cc) {}
} task[maxn];
int tc[maxn] = { 0 }, tcg[maxn] = { 0 }, tcc[maxn] = { 0 }, t[maxn] = { 0 };
int n;

bool cmp(Task& a, Task& b) {
    if (a.c != b.c)
        return a.c < b.c;
    if (a.cg != b.cg)
        return a.cg < b.cg;
    return a.cc < b.cc;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    int c, cc, cg, ccg;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d%d", &c, &cc, &cg, &ccg);
        task[i] = Task(c, cg, min(cc, ccg));
    }
    sort(task, task + n, cmp);
    for (int i = 1; i <= n; ++i) {
        Task& tmp = task[i];
        //如果第i个任务选择c，则可以把时间加到tc上，也可以把时间加到tcg上
        int t1 = max(tc[i - 1] + tmp.c, tcg[i - 1]) + tcc[i - 1];
        int t2 = max(tc[i - 1], tcg[i - 1] + tmp.c) + tcc[i - 1];
        //如果第i个任务选择cg，则要把时间加到tcg上
        int t3 = max(tc[i - 1], tcg[i - 1] + tmp.cg) + tcc[i - 1];
        //如果第i个任务选择cc，则要把时间加到tcc上
        int t4 = max(tc[i - 1], tcg[i - 1]) + tcc[i - 1] + tmp.cc;
        //选择的优先级是t1->t2->t3->t4
        tc[i] = tc[i - 1];
        tcg[i] = tcg[i - 1];
        tcc[i] = tcc[i - 1];
        if (t1 <= t2 && t1 <= t3 && t1 <= t4) {
            tc[i] += tmp.c;
            t[i] = t1;
        }
        if (t2 < t1 && t2 <= t3 && t2 <= t4) {
            tcg[i] += tmp.c;
            t[i] = t2;
        }
        if (t3 < t1 && t3 < t2 && t3 <= t4) {
            tcg[i] += tmp.cg;
            t[i] = t3;
        }
        if (t4 < t1 && t4 < t2 && t4 < t3) {
            tcc[i] += tmp.cc;
            t[i] = t4;
        }
    }
    printf("%d", t[n]);
    return 0;
}