#include <iostream>
using namespace std;
// #define DEBUG

//为了与月份对应，下标为1-12
int daysOfMonth[] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
struct Date {
    int year, month, day, week;
    Date() {}
    Date(int _year, int _month, int _day, int _week)
        : year(_year)
        , month(_month)
        , day(_day)
        , week(_week) {}
    bool runYear() {
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
            return true;
        return false;
    }
    Date& operator++() {
        ++week;
        if (week == 8)
            week = 1;
        //是闰年
        if (month == 2 && day == 28) {
            if (runYear())
                ++day;
            else {
                day = 1;
                month = 3;
            }
        } else {
            if (day == daysOfMonth[month]) {
                day = 1;
                if (month == 12) {
                    month = 1;
                    ++year;
                } else
                    ++month;
            } else
                ++day;
        }
    }
} date(1850, 1, 1, 2);

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    int a, b, c, y1, y2, cnt;
    scanf("%d%d%d%d%d", &a, &b, &c, &y1, &y2);
    for (int y = y1; y <= y2; ++y) {
        cnt = 0;
        while (date.year < y)
            ++date;
        for (;;) {
            if (date.month == a && date.week == c) {
                ++cnt;
                //找到了
                if (cnt == b) {
                    printf("%d/%02d/%02d\n", date.year, date.month, date.day);
                    break;
                }
            }
            ++date;
            //没找到
            if (date.year > y) {
                printf("none\n");
                break;
            }
        }
    }
    return 0;
}