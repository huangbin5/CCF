/**
 * 很复杂，整理一下思路
 * 1、读入每个任务，将符合要求的周、月、日、时、分分别记录在set中（不用vector主要是为了查找）
 * 2、先遍历两个日期中的每一天，然后遍历每一天的符合要求的时间，将执行列表保存在Result结构体向量中
 * 3、将结果向量按时间排序，时间相同按任务id排序
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
// #define DEBUG

#define I(x) ((x) - '0')
enum EleId { MINUTE, HOUR, DAY, MONTH, WEEK };
string months[] = { "", "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
string weeks[] = { "sun", "mon", "tue", "wed", "thu", "fri", "sat" };
int daysOfMonth[][2] = { { 0, 0 }, { 31, 31 }, { 28, 29 }, { 31, 31 }, { 30, 30 }, { 31, 31 }, { 30, 30 }, { 31, 31 }, { 31, 31 },
    { 30, 30 }, { 31, 31 }, { 30, 30 }, { 31, 31 } };

struct Date {
    int year, month, day, week;
    Date() {}
    Date(int _year, int _month, int _day, int _week)
        : year(_year)
        , month(_month)
        , day(_day)
        , week(_week) {}
    bool isRun() {
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
            return true;
        return false;
    }
    Date& operator++() {
        ++day;
        if (day > daysOfMonth[month][isRun()]) {
            day = 1;
            ++month;
            if (month > 12) {
                month = 1;
                ++year;
            }
        }
        week = (week + 1) % 7;
        return *this;
    }
    bool operator<(const Date& d) const {
        if (year != d.year)
            return year < d.year;
        if (month != d.month)
            return month < d.month;
        return day < d.day;
    }
    bool operator==(const Date& d) const {
        if (*this < d || d < *this)
            return false;
        return true;
    }
    //根据日期计算周
    void getWeek() {
        Date d(1970, 1, 1, 4);
        while (d < *this)
            ++d;
        this->week = d.week;
    }
};
struct Time {
    int hour, minute;
    Time() {}
    Time(int _hour, int _minute)
        : hour(_hour)
        , minute(_minute) {}
    bool operator<(const Time& t) const {
        if (hour != t.hour)
            return hour < t.hour;
        return minute < t.minute;
    }
};
struct DateTime {
    Date date;
    Time time;
    bool operator<(const DateTime& dt) const {
        if (date < dt.date || dt.date < date)
            return date < dt.date;
        return time < dt.time;
    }
} from, to;

struct Task {
    // 0-minute, 1-hour, 2-day, 3-month, 4-week
    bool eleFlag[5];
    set<int> ele[5];
    string name;
    int id;
    void clear() {
        for (int i = 0; i < 5; ++i) {
            eleFlag[i] = false;
            ele[i].clear();
            name.clear();
        }
    }
} task;

struct Result {
    DateTime dateTime;
    string name;
    int id;
    bool operator<(const Result& r) const {
        if (dateTime < r.dateTime || r.dateTime < dateTime)
            return dateTime < r.dateTime;
        return id < r.id;
    }
} result;
vector<Result> ans;

void strToTime(string& s, DateTime& t) {
    t.date.year = I(s[0]) * 1000 + I(s[1]) * 100 + I(s[2]) * 10 + I(s[3]);
    t.date.month = I(s[4]) * 10 + I(s[5]);
    t.date.day = I(s[6]) * 10 + I(s[7]);
    t.date.getWeek();
    t.time.hour = I(s[8]) * 10 + I(s[9]);
    t.time.minute = I(s[10]) * 10 + I(s[11]);
}

int strToInt(string s) {
    int ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        ans = ans * 10 + I(s[i]);
    }
    return ans;
}

int getIndex(string* sp, string& s) {
    int ans = 0;
    while (sp[ans] != s)
        ++ans;
    return ans;
}

//将符合要求的周、月、日、时、分分别记录在set中
void formatEle(string& ele, int id) {
    if (ele[0] == '*') {
        task.eleFlag[id] = true;
        //小时和分钟为*时仍然存在set中是为了下面获取结果方便
        if (id == HOUR)
            for (int i = 0; i < 24; ++i)
                task.ele[HOUR].insert(i);
        if (id == MINUTE)
            for (int i = 0; i < 60; ++i)
                task.ele[MINUTE].insert(i);
    } else {
        task.eleFlag[id] = false;
        //方便下面for循环统一处理
        ele += ',';
        string subEle, subEle1, subEle2;
        int pos1 = 0, pos2, pos3;
        for (;;) {
            //读取每一个以,分隔的时间
            pos2 = ele.find(',', pos1);
            subEle = ele.substr(pos1, pos2 - pos1);
            //转化为小写
            transform(subEle.begin(), subEle.end(), subEle.begin(), ::tolower);
            pos3 = subEle.find('-');
            if (pos3 == -1) {
                //如果是一个时间
                int value;
                if (subEle[0] < '0' || subEle[0] > '9') {
                    if (id == MONTH)
                        value = getIndex(months, subEle);
                    else
                        value = getIndex(weeks, subEle);
                } else
                    value = strToInt(subEle);
                task.ele[id].insert(value);
            } else {
                //如果是一个时间段
                subEle1 = subEle.substr(0, pos3);
                transform(subEle1.begin(), subEle1.end(), subEle1.begin(), ::tolower);
                subEle2 = subEle.substr(pos3 + 1);
                transform(subEle2.begin(), subEle2.end(), subEle2.begin(), ::tolower);
                int start, end;
                //有可能出现“时间段前面是用数字表示”“而后面是用字母表示”的情况，因此要分开处理
                if (subEle1[0] < '0' || subEle1[0] > '9') {
                    if (id == MONTH)
                        start = getIndex(months, subEle1);
                    else
                        start = getIndex(weeks, subEle1);
                } else
                    start = strToInt(subEle1);
                if (subEle2[0] < '0' || subEle2[0] > '9') {
                    if (id == MONTH)
                        end = getIndex(months, subEle2);
                    else
                        end = getIndex(weeks, subEle2);
                } else
                    end = strToInt(subEle2);
                for (int i = start; i <= end; ++i)
                    task.ele[id].insert(i);
            }
            pos1 = pos2 + 1;
            if (pos1 == ele.size())
                break;
        }
    }
}

//读入任务
void formatTask(int id) {
    task.clear();
    string ele[5], name;
    cin >> ele[0] >> ele[1] >> ele[2] >> ele[3] >> ele[4] >> name;
    for (int i = 0; i < 5; ++i)
        formatEle(ele[i], i);
    task.name = name;
    task.id = id;
}

//调试任务读取的结果对不对
void printTask() {
    cout << task.name << endl;
    for (int i = 0; i < 5; ++i) {
        cout << i << ":";
        if (task.eleFlag[i])
            cout << " *" << endl;
        else {
            for (set<int>::iterator it = task.ele[i].begin(); it != task.ele[i].end(); ++it)
                cout << " " << *it;
            cout << endl;
        }
    }
}

//周、月、日符合要求
bool checkDate(Date& dt) {
    if ((task.eleFlag[MONTH] || task.ele[MONTH].count(dt.month)) && (task.eleFlag[DAY] || task.ele[DAY].count(dt.day))
        && (task.eleFlag[WEEK] || task.ele[WEEK].count(dt.week)))
        return true;
    return false;
}

void getAns() {
    Date curDate = from.date, toDate = to.date;
    //遍历起止时间中的每一天
    while (!(toDate < curDate)) {
        result.dateTime.date = curDate;
        if (checkDate(curDate)) {
            //遍历每一天中符合要求的时间
            for (set<int>::iterator it1 = task.ele[HOUR].begin(); it1 != task.ele[HOUR].end(); ++it1) {
                for (set<int>::iterator it2 = task.ele[MINUTE].begin(); it2 != task.ele[MINUTE].end(); ++it2) {
                    Time curTime(*it1, *it2);
                    if (curDate == from.date && curTime < from.time)
                        continue;
                    //不包括结束时间
                    if (curDate == to.date && !(curTime < to.time))
                        continue;
                    result.dateTime.time = curTime;
                    result.name = task.name;
                    result.id = task.id;
                    ans.push_back(result);
                }
            }
        }
        ++curDate;
    }
}

//打印结果
void printAns() {
    for (int i = 0; i < ans.size(); ++i) {
        Date& date = ans[i].dateTime.date;
        Time& time = ans[i].dateTime.time;
        printf("%d%02d%02d%02d%02d %s\n", date.year, date.month, date.day, time.hour, time.minute, ans[i].name.c_str());
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    int n, id = 0;
    string t1, t2;
    cin >> n >> t1 >> t2;
    //获取起止时间
    strToTime(t1, from);
    strToTime(t2, to);
    while (n--) {
        formatTask(id++);
        // printTask();
        getAns();
    }
    sort(ans.begin(), ans.end());
    printAns();
    return 0;
}