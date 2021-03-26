#include <bits/stdc++.h>
using namespace std;
#define eps 1e-9
typedef long long ll;

const int maxn = 1e6;

void add_vector() {
    clock_t start = clock();
    vector<int> v;
    for (int i = 0; i < maxn; ++i) {
        int tmp = rand();
        v.push_back(tmp);
        if (tmp % 1000000 == 0)
            sort(v.begin(), v.end());
    }
    clock_t end = clock();
    printf("%d\n", end - start);
}

void add_set() {
    clock_t start = clock();
    set<int> s;
    for (int i = 0; i < maxn; ++i) {
        int tmp = rand();
        s.insert(tmp);
        if (tmp % 1000000 == 0)
            int p = 1;
    }
    clock_t end = clock();
    printf("%d\n", end - start);
}

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    srand((unsigned int)time(NULL));
    add_vector();
    add_set();
#ifndef DEBUG
    system("pause");
#endif
    return 0;
}