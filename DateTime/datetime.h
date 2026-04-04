#ifndef DATETIME_H
#define DATETIME_H

class DateTime {
private:
    int year, month, day;
    int hour, minute, second;

    static const char* monthNames[13];
    static const char* dayNames[7];

    bool      isLeapYear(int y)       const;
    int       daysInMonth(int m, int y) const;
    long long toJulian()              const;

public:
    DateTime();
    DateTime(int year, int month, int day,
             int hour = 0, int minute = 0, int second = 0);

    void input();
    bool isValid() const;

    void printFormat1() const;   
    void printFormat2() const;   
    void printFormat3() const;   
    void printISO()     const;  

    int         dayOfWeek()     const;  
    const char* dayOfWeekName() const;

    long long diffDays(const DateTime& other) const;

    static DateTime calculateEaster(int year);
};

#endif
