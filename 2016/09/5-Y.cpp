/**
 * 100分
 */
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define N 305010
int n, q;
int x[N];
int y[N];
struct SRT {
    int v;
    int idx;
} z[N];
bool cmpByV(SRT a, SRT b) { return a.v < b.v; }
void reorder(int* x) {
    for (int i = 1; i <= n; i++) {
        z[i].v = x[i];
        z[i].idx = i;
    }
    sort(z + 1, z + n + 1, cmpByV);
    int newVal = 1;
    x[z[1].idx] = newVal;
    for (int i = 2; i <= n; i++) {
        if (z[i].v != z[i - 1].v)
            newVal++;
        x[z[i].idx] = newVal;
    }
}
int readInt() {
    char ch = getchar();
    while (ch != '-' && (ch < '0' || ch > '9'))
        ch = getchar();
    int flag = 1;
    if (ch == '-') {
        flag = -1;
        ch = getchar();
    }
    int x = 0;
    do {
        x = x * 10 + ch - '0';
        ch = getchar();
    } while (ch >= '0' && ch <= '9');
    return x * flag;
}
void read() {
    n = readInt();
    q = readInt();
    for (int i = 1; i <= n; i++) {
        x[i] = readInt();
        y[i] = readInt();
    }
    reorder(x);
    reorder(y);
    // for (int i=1;i<=n;i++)printf("(%d,%d)\n",x[i],y[i]);
    // system("pause");
}
/*
short left[N][N],top[N][N];
int min(int a,int b){
  return a<b?a:b;
}
void solve(){
  memset(left,0,sizeof(left));
  memset(top,0,sizeof(top));
  for (int i=1;i<=n;i++) left[x[i]][y[i]]=top[x[i]][y[i]]=1;
  for (int i=1;i<=n;i++)
    for (int j=1;j<=n;j++){
      left[i][j]+=left[i][j-1];
    }
  for (int j=1;j<=n;j++)
  for (int i=1;i<=n;i++)
    top[i][j]+=top[i-1][j];
  int best=0,best_cnt;
  for (int i=1;i<=n;i++)
  for (int j=1;j<=n;j++){
    int level=min(left[i][j-1],left[i][n]-left[i][j]);
    int tmp=min(top[i-1][j],top[n][j]-top[i][j]);
    level=min(level,tmp);
    if (level>best){
      best=level;
      best_cnt=1;
    }else
    if (level==best) best_cnt++;
  }
  if (q==1)printf("%d\n",best);
  else printf("%d\n",best_cnt);
}*/
int max(int a, int b) { return a < b ? b : a; }
struct POINT {
    int x, y;
} p[N];
bool cmpByX(POINT a, POINT b) { return a.y < b.y || (a.y == b.y && a.x < b.x); }
int projx[N]; //点到x的投影
struct NODE {
    int l;
    int r;
    int tval, bval; //叶子节点信息
    int mx;
    NODE* ch[2];
    NODE() { ch[0] = ch[1] = NULL; }
    inline void maintain() {
        if (ch[0] == NULL)
            return;
        mx = max(ch[0]->mx, ch[1]->mx);
    }
    void build(int ll, int rr) { //按照projx[N]进行初始化
        l = ll;
        r = rr;
        if (l == r - 1) {
            tval = projx[r];
            bval = 0;
            mx = 0;
            return;
        }
        ch[0] = new NODE();
        ch[0]->build(l, (l + r) >> 1);
        ch[1] = new NODE();
        ch[1]->build((l + r) >> 1, r);
        maintain();
    }
    void insTop(int pos, int v) {
        if (pos - 1 >= r || pos <= l)
            return;
        if (pos - 1 == l && pos == r) {
            tval += v;
            mx = min(tval, bval);
            return;
        }
        ch[0]->insTop(pos, v);
        ch[1]->insTop(pos, v);
        maintain();
    }
    void insBot(int pos, int v) {
        if (pos - 1 >= r || pos <= l)
            return;
        if (pos - 1 == l && pos == r) {
            bval += v;
            mx = min(tval, bval);
            return;
        }
        ch[0]->insBot(pos, v);
        ch[1]->insBot(pos, v);
        maintain();
    }
    int getMax(int ll, int rr) {
        if (r <= ll || l >= rr)
            return 0;
        if (l >= ll && r <= rr)
            return mx;
        return max(ch[0]->getMax(ll, rr), ch[1]->getMax(ll, rr));
    }
    void show() {
        if (l == r - 1) {
            printf("(%d:%d,%d)", r, tval, bval);
            return;
        }
        ch[0]->show();
        ch[1]->show();
    }
} * root;
void pre() {
    memset(projx, 0, sizeof(projx));
    for (int i = 1; i <= n; i++) {
        p[i].x = x[i];
        p[i].y = y[i];
        projx[x[i]]++;
    }
    sort(p + 1, p + n + 1, cmpByX); //点按y第一x第二排序
    root = new NODE();
    root->build(0, n);
}
#define FOR(i, st, ed) for (int i = st; i <= ed; i++)
int best;
struct NODE2 {
    int l, r;
    NODE2* ch[2];
    int tval;
    int bval;
    int cnt; //上下均大于best的统计
    NODE2() { ch[0] = ch[1] = NULL; }
    void maintain() {
        if (ch[0] == NULL)
            return;
        cnt = ch[0]->cnt + ch[1]->cnt;
    }
    void build(int ll, int rr) { //按照projx[N]进行初始化
        l = ll;
        r = rr;
        if (l == r - 1) {
            tval = projx[r];
            bval = 0;
            cnt = 0;
            return;
        }
        ch[0] = new NODE2();
        ch[0]->build(l, (l + r) >> 1);
        ch[1] = new NODE2();
        ch[1]->build((l + r) >> 1, r);
        maintain();
    }
    void insTop(int pos, int v) {
        if (pos - 1 >= r || pos <= l)
            return;
        if (pos - 1 == l && pos == r) {
            tval += v;
            if (bval >= best && tval >= best)
                cnt = 1;
            return;
        }
        ch[0]->insTop(pos, v);
        ch[1]->insTop(pos, v);
        maintain();
    }
    void insBot(int pos, int v) {
        if (pos - 1 >= r || pos <= l)
            return;
        if (pos - 1 == l && pos == r) {
            bval += v;
            cnt = 0;
            if (bval >= best && tval >= best)
                cnt = 1;
            return;
        }
        ch[0]->insBot(pos, v);
        ch[1]->insBot(pos, v);
        maintain();
    }
    int count(int ll, int rr) {
        if (r <= ll || l >= rr)
            return 0;
        if (l >= ll && r <= rr)
            return cnt;
        return ch[0]->count(ll, rr) + ch[1]->count(ll, rr);
    }
    void show() {
        if (l == r - 1) {
            printf("(%d:%d %d %d)", r, tval, bval, cnt);
            return;
        }
        ch[0]->show();
        ch[1]->show();
    }
} * root2;
void solve2_get_cnt() { //已知best，求方法数
    int curIdx = 1;
    root2 = new NODE2();
    root2->build(0, n);
    int best_cnt = 0;
    while (curIdx <= n) {
        int yy = p[curIdx].y;
        int stIdx = curIdx;
        int edIdx = curIdx;
        while (edIdx <= n && p[edIdx + 1].y == yy)
            edIdx++;
        curIdx = edIdx + 1;
        int pntCnt = edIdx - stIdx + 1;
        // p[stIdx..edIdx]这些点y坐标均为yy，计算y坐标为yy的ans
        for (int i = stIdx; i <= edIdx; i++)
            root2->insTop(p[i].x, -1); //从上方减去节点
        // printf("root2:");root2->show();putchar('\n');
        int p1 = stIdx + best - 1;
        int p2 = edIdx - best + 1;
        if (p1 < p2)
            best_cnt += root2->count(p[p1].x, p[p2].x - 1);
        //
        for (int i = stIdx; i <= edIdx; i++)
            root2->insBot(p[i].x, 1); //下方加上
        // FOR(i,stIdx,edIdx) printf("(%d,%d) ",p[i].x,p[i].y);putchar('\n');
    }
    printf("%d\n", best_cnt);
}
void solve2() {
    best = 0;
    pre();
    int curIdx = 1;
    while (curIdx <= n) {
        int yy = p[curIdx].y;
        int stIdx = curIdx;
        int edIdx = curIdx;
        while (edIdx <= n && p[edIdx + 1].y == yy)
            edIdx++;
        curIdx = edIdx + 1;
        int pntCnt = edIdx - stIdx + 1;
        // p[stIdx..edIdx]这些点y坐标均为yy，计算y坐标为yy的ans
        for (int i = stIdx; i <= edIdx; i++)
            root->insTop(p[i].x, -1); //从上方减去节点
        // printf("root:");root->show();putchar('\n');
        int p1 = pntCnt / 2 + stIdx - 1;
        int p2 = edIdx - pntCnt / 2 + 1;
        while (p1 >= stIdx && p1 - stIdx + 1 > best) {
            int ans = p1 - stIdx + 1;
            int tbMx = root->getMax(p[p1].x, p[p2].x - 1);
            // printf("(%d,%d) mx=%d\n",p[p1].x,p[p2].x-1,tbMx);
            ans = min(ans, tbMx);
            best = max(ans, best);
            p1--;
            p2++;
        }
        //
        for (int i = stIdx; i <= edIdx; i++)
            root->insBot(p[i].x, 1); //下方加上
        // FOR(i,stIdx,edIdx) printf("(%d,%d) ",p[i].x,p[i].y);putchar('\n');
    }
    if (q == 1) {
        printf("%d\n", best);
        return;
    } else
        solve2_get_cnt();
    // q=2
}
int main() {
    read();
    // solve();
    solve2();
    return 0;
}