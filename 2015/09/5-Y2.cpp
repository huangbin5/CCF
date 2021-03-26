/**
 * 90分
 */
#include <iostream>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#define ACMXNODE 110 // AC自动机节点数(最大为所有字符串字符个数和)
int charIdx(char ch) { return ch - 'a'; }
#define CHARSIZE 30 //不同字符个数(128可以处理大部分情况，空间紧张可以减少这个值,但要保证charIdx每个字符都对应一个下标)
/*
  用法：
  ac.clearMap();
  ac.ins(str,val);//相同字符串会相互覆盖
  ac.getfail()
*/
int cnt[ACMXNODE]; // cnt[u]：插入的字符串中，等于字符串u的某个后缀的字符串个数
class ACAUTO {
public:
    int sz;
    int ch[ACMXNODE][CHARSIZE];
    int val[ACMXNODE]; //节点标记值，0表示非叶子节点。叶子节点记录一个自定义值（如是第几个字符串）。（相同字符串会互相覆盖）
    int f[ACMXNODE]; // fail数组
    int last[ACMXNODE]; ////last[u]：上一个u结尾的字符串。如有两个字符串(abcd,bc)，节点u表示abc,则节点last[u]指向bc。
    int print(int i, int j);

public:
    ACAUTO();
    //初始化+建图
    int clearMap(); //初始化
    int ins(char* s, int v); //插入一个字符串，v代表字符串结尾节点标记值。(0：非字符串结尾，其他：自定义)
    int getFail(); //建立失配指针。bfs查找
    int kmpFind(char* T); //找出trie树中所有为T子串的字符串
};
ACAUTO::ACAUTO() { clearMap(); }
int ACAUTO::clearMap() {
    sz = 1;
    memset(ch[0], 0, sizeof(ch[0]));
    memset(val, 0, sizeof(val));
    memset(cnt, 0, sizeof(cnt));
    return 0;
}
int ACAUTO::ins(char* s, int v = 1) {
    int u = 0;
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
        int c = charIdx(s[i]);
        if (!ch[u][c]) {
            memset(ch[sz], 0, sizeof(ch[sz]));
            val[sz] = 0;
            ch[u][c] = sz++;
        }
        u = ch[u][c];
    }
    val[u] = v;
    return 0;
}
int ACAUTO::getFail() {
    queue<int> q;
    //先处理节点0的fail值
    f[0] = 0;
    for (int c = 0; c < CHARSIZE; c++) {
        int u = ch[0][c];
        if (u) {
            f[u] = 0;
            q.push(u);
            last[u] = 0;
        }
    }
    //处理其他节点
    while (!q.empty()) {
        int r = q.front();
        q.pop();
        for (int c = 0; c < CHARSIZE; c++) {
            int u = ch[r][c];
            if (!u) {
                ch[r][c] = ch[f[r]][c];
                continue;
            }
            q.push(u);
            f[u] = ch[f[r]][c];
            last[u] = val[f[u]] ? f[u] : last[f[u]];
            cnt[u] = cnt[f[u]] + (val[u] > 0);
        }
    }
}

int ACAUTO::kmpFind(char* T) {
    int n = strlen(T);
    int j = 0;
    for (int i = 0; i < n; i++) {
        int c = charIdx(T[i]);
        j = ch[j][c];
        printf("cnt=%d\n", cnt[j]);
        if (val[j])
            print(i, j);
        else if (last[j])
            print(i, last[j]);
    }
}
int ACAUTO::print(int i, int j) {
    if (j) {
        printf("模板串T第%d个字符结尾子串和AC自动机编号为%d的一样,last[%d]=%d\n", i + 1, val[j], j, last[j]);
        print(i, last[j]);
    }
    return 0;
}
ACAUTO ac;
long long f[101000][110];
pair<int, int> path[101000][110];
vector<int> g[110];
int nodeList[1100], nodeListSz = 0;
int repList[1100], repListSz = 0, repGain = 0;
void outputPath(int i, int u) {
    if (i == 0)
        return;
    outputPath(i - 1, path[i][u].first);
    nodeList[++nodeListSz] = u;
    // putchar(path[i][u].second+'a');
}
int main() {
    int n;
    long long m;
    scanf("%d", &n);
    cin >> m;
    char s[110];
    ac.clearMap();
    for (int i = 1; i <= n; i++) {
        scanf("%s", s);
        ac.ins(s, i);
    }
    ac.getFail();
    //
    for (int u = 0; u < ac.sz; u++) {
        for (int c = 0; c < CHARSIZE; c++) {
            int v = ac.ch[u][c]; // u->v (c)
            g[v].push_back(u);
        }
    }
    memset(f, 255, sizeof(f));
    memset(path, 0, sizeof(path));
    f[0][0] = 0;
    int sz = ac.sz;
    int rep = 0;
#define FOR(i, s, t) for (int i = s; i <= t; i++)
    for (int i = 1; i <= 1000; i++) {
        f[i][sz] = 0;
        for (int u = 0; u < sz; u++) {
            for (int j = 0; j < g[u].size(); j++) {
                int v = g[u][j]; // v->u
                if (f[i - 1][v] == -1)
                    continue;
                if (f[i - 1][v] > f[i][u]) {
                    f[i][u] = f[i - 1][v];
                    path[i][u].first = v;
                }
            }
            //
            int v = path[i][u].first;
            FOR(c, 0, CHARSIZE - 1) if (ac.ch[v][c] == u) {
                path[i][u].second = c;
                break;
            }
            //
            if (f[i][u] != -1)
                f[i][u] += cnt[u];
            if (f[i][sz] < f[i][u]) {
                f[i][sz] = f[i][u];
                path[i][sz].first = u;
            }
        }
    }
    outputPath(1000, path[1000][sz].first); // putchar('\n');

    // FOR(i,1,nodeListSz) printf("%d ",nodeList[i]);putchar('\n');
    FOR(i, 400, 1000) {
        // printf("%d ->\n",nodeList[i]);
        repList[++repListSz] = nodeList[i];
        if (nodeList[i] == nodeList[399]) {
            repGain = f[i][sz] - f[399][sz];
            break;
        }
    }
    // FOR(i,1,repListSz) printf("%d ",repList[i]);putchar('\n');
    // printf("RepGain=%d\n",repGain);
    long long p = max(m / repListSz - 6, 0ll); // p段的重复串提取出来
    m -= p * repListSz;
    cout << f[m][sz] + repGain * p << endl;
    return 0;
}