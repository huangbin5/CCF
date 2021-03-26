#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef unsigned int uint;
// #define DEBUG

const int maxn = 100005;
int n;
struct IP {
    uint seg, len;
    IP() { seg = 0; }

    bool contain(IP& ip) {
        /**
         * 小知识：当len=32时，左移32位并不会得到0
         * 因为<<a时，a最大为31，当超过31时，会先执行a&=31即a%=32，再执行<<a
         * 因此当len=32时实际上执行的是<<0
         */
        uint mask = len == 0 ? 0 : 0xffffffff << (32 - len);
        return (seg & mask) == (ip.seg & mask);
    }
};
vector<IP> v, ans;

bool cmp(IP& a, IP& b) {
    if (a.seg != b.seg)
        return a.seg < b.seg;
    return a.len < b.len;
}

int stringToInt(string s) {
    int ret = 0;
    for (int i = 0; i < s.size(); ++i)
        ret = ret * 10 + s[i] - '0';
    return ret;
}

void getInput() {
    string line;
    cin >> line;
    int cnt = 0;
    IP ip;
    int sepPos = line.find('/');
    if (sepPos == -1)
        sepPos = line.size();
    int pos1 = 0, pos2 = 0;
    //处理ip的4个部分
    while (pos2 != sepPos) {
        pos2 = line.find('.', pos1);
        if (pos2 == -1)
            pos2 = sepPos;
        ip.seg = (ip.seg << 8) + stringToInt(line.substr(pos1, pos2 - pos1));
        ++cnt;
        pos1 = pos2 + 1;
    }
    //前缀长度
    if (sepPos == line.size())
        ip.len = cnt * 8;
    else
        ip.len = stringToInt(line.substr(sepPos + 1));
    //加上剩下的0
    for (; cnt < 4; ++cnt)
        ip.seg <<= 8;
    v.push_back(ip);
}

void getResult() {
    //第一步：排序
    sort(v.begin(), v.end(), cmp);
    //第二步：从小到大合并
    int i = 0, j = 1;
    while (i < v.size()) {
        //最后一个不要漏掉了
        if (j > v.size() || !v[i].contain(v[j])) {
            ans.push_back(v[i]);
            i = j;
        }
        ++j;
    }
    //第三步：同级合并
    i = 0;
    while (i + 1 < ans.size()) {
        //前缀长度相等时才要合并
        if (ans[i].len == ans[i + 1].len) {
            IP ip = ans[i];
            //特殊情况
            if (ip.len == 0) {
                printf("0.0.0.0/0\n");
                return;
            }
            //将第len位设置为0
            ip.seg &= ~(1 << (32 - ip.len));
            --ip.len;
            if (ip.contain(ans[i]) && ip.contain(ans[i + 1])) {
                ans.erase(ans.begin() + i, ans.begin() + i + 2);
                ans.insert(ans.begin() + i, ip);
                if (i != 0)
                    --i;
            } else
                ++i;
        } else
            ++i;
    }
    for (i = 0; i < ans.size(); ++i) {
        uint seg = ans[i].seg;
        printf("%d.%d.%d.%d/%d\n", seg >> 24, (seg << 8) >> 24, (seg << 16) >> 24, (seg << 24) >> 24, ans[i].len);
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    while (n--)
        getInput();
    //特殊情况
    if (v.size() == 1) {
        uint seg = v[0].seg;
        printf("%d.%d.%d.%d/%d\n", seg >> 24, (seg << 8) >> 24, (seg << 16) >> 24, (seg << 24) >> 24, v[0].len);
        return 0;
    }
    getResult();
    return 0;
}