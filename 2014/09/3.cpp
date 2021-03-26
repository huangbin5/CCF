#include <algorithm>
#include <iostream>
using namespace std;
// #define DEBUG

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    string pattern, sentence;
    int n, sensitive;
    cin >> pattern >> sensitive >> n;
    if (!sensitive)
        transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
    while (n--) {
        cin >> sentence;
        if (!sensitive) {
            string tmp;
            //注意要设置大小，否则转换成小写后tmp为空
            tmp.resize(sentence.size());
            transform(sentence.begin(), sentence.end(), tmp.begin(), ::tolower);
            if (tmp.find(pattern) != -1)
                cout << sentence << endl;
        } else {
            if (sentence.find(pattern) != -1)
                cout << sentence << endl;
        }
    }
    return 0;
}