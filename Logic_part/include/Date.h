//
// Created by 孙璋亮 on 2019-08-28.
//

#ifndef COURIER_CLIENT_DATE_H
#define COURIER_CLIENT_DATE_H


class Date {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
public:
    int getYear() const;

    void setYear(int year);

    int getMonth() const;

    void setMonth(int month);

    int getDay() const;

    void setDay(int day);

    int getHour() const;

    void setHour(int hour);

    int getMinute() const;

    void setMinute(int minute);

    int getSecond() const;

    void setSecond(int second);
};


#endif //COURIER_CLIENT_DATE_H
