//
// Created by 孙璋亮 on 2019-08-28.
//

#include "Date.h"

int Date::getYear() const {
    return year;
}

void Date::setYear(int year) {
    Date::year = year;
}

int Date::getMonth() const {
    return month;
}

void Date::setMonth(int month) {
    Date::month = month;
}

int Date::getDay() const {
    return day;
}

void Date::setDay(int day) {
    Date::day = day;
}

int Date::getHour() const {
    return hour;
}

void Date::setHour(int hour) {
    Date::hour = hour;
}

int Date::getMinute() const {
    return minute;
}

void Date::setMinute(int minute) {
    Date::minute = minute;
}

int Date::getSecond() const {
    return second;
}

void Date::setSecond(int second) {
    Date::second = second;
}
