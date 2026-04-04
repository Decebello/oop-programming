#include <iostream>
#include "datetime.h"

using namespace std;

const char* DateTime::monthNames[13] = {
    "",
    "января",   "февраля", "марта",    "апреля",
    "мая",      "июня",    "июля",     "августа",
    "сентября", "октября", "ноября",   "декабря"
};

const char* DateTime::dayNames[7] = {
    "Понедельник", "Вторник",  "Среда",
    "Четверг",     "Пятница",  "Суббота", "Воскресенье"
};

static void printTwoDigit(int n) {
    if (n < 10) cout << '0';
    cout << n;
}

static void printFourDigit(int n) {
    if (n < 1000) cout << '0';
    if (n < 100)  cout << '0';
    if (n < 10)   cout << '0';
    cout << n;
}

bool DateTime::isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int DateTime::daysInMonth(int m, int y) const {
    const int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && isLeapYear(y)) return 29;
    return days[m];
}

long long DateTime::toJulian() const {
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    return (long long)day
         + (153 * m + 2) / 5
         + 365LL * y
         + y / 4
         - y / 100
         + y / 400
         - 32045;
}

DateTime::DateTime()
    : year(2000), month(1), day(1), hour(0), minute(0), second(0) {}

DateTime::DateTime(int y, int m, int d, int h, int min, int s)
    : year(y), month(m), day(d), hour(h), minute(min), second(s) {}

void DateTime::input() {
    cout << "Введите дату-время (yyyy-MM-ddThh:mm:ss): ";
    char c;
    cin >> year >> c >> month >> c >> day >> c >> hour >> c >> minute >> c >> second;
}

bool DateTime::isValid() const {
    if (month < 1 || month > 12)                    return false;
    if (day   < 1 || day > daysInMonth(month, year)) return false;
    if (hour   < 0 || hour   > 23)                   return false;
    if (minute < 0 || minute > 59)                   return false;
    if (second < 0 || second > 59)                   return false;
    return true;
}

void DateTime::printFormat1() const {          
    cout << day << '.';
    printTwoDigit(month);
    cout << '.';
    printFourDigit(year);
}

void DateTime::printFormat2() const {         
    cout << day << ' ' << monthNames[month] << ' ' << year;
}

void DateTime::printFormat3() const {         
    printTwoDigit(day);
    cout << '.';
    printTwoDigit(month);
    cout << '.';
    printTwoDigit(year % 100);
}

void DateTime::printISO() const {              
    printFourDigit(year); cout << '-';
    printTwoDigit(month); cout << '-';
    printTwoDigit(day);   cout << 'T';
    printTwoDigit(hour);  cout << ':';
    printTwoDigit(minute); cout << ':';
    printTwoDigit(second);
}

int DateTime::dayOfWeek() const {
    const int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    int y = year;
    if (month < 3) y--;
    int dow = (y + y / 4 - y / 100 + y / 400 + t[month - 1] + day) % 7;
    return (dow + 6) % 7;
}

const char* DateTime::dayOfWeekName() const {
    return dayNames[dayOfWeek()];
}

long long DateTime::diffDays(const DateTime& other) const {
    long long diff = toJulian() - other.toJulian();
    return diff < 0 ? -diff : diff;
}

DateTime DateTime::calculateEaster(int y) {
    int a  = y % 19;
    int b  = y / 100;
    int c  = y % 100;
    int d  = b / 4;
    int e  = b % 4;
    int f  = (b + 8) / 25;
    int g  = (b - f + 1) / 3;
    int h  = (19 * a + b - d - g + 15) % 30;
    int i  = c / 4;
    int k  = c % 4;
    int l  = (32 + 2 * e + 2 * i - h - k) % 7;
    int m  = (a + 11 * h + 22 * l) / 451;
    int mo = (h + l - 7 * m + 114) / 31;
    int da = (h + l - 7 * m + 114) % 31 + 1;
    return DateTime(y, mo, da);
}
