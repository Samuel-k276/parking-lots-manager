#include <stdio.h>

#include "time.h"

/** The number of days in each month */
const short daysInTheMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

Time time0() {
    Time time;
    time.date.day = 1;
    time.date.month = 1;
    time.date.year = 1;
    time.hours.hours = 0;
    time.hours.minutes = 0;
 
    return time;
}

void changeTime(Time *dateToChange, Time newDate) {
        *dateToChange = newDate;
}

Time newTime(int day, int month, int year, int hours, int minutes) {
        Time time;
        time.date.day = day;
        time.date.month = month;
        time.date.year = year;
        time.hours.hours = hours;
        time.hours.minutes = minutes;

        return time;
}

short invalidTime(Time date) {
        return (date.date.month > 12 || date.date.month < 1 || date.date.day < 1
                    || date.date.day > daysInTheMonth[date.date.month - 1] || 
                    date.hours.minutes > 59 || date.hours.minutes < 0 || 
                    date.hours.hours > 23 || date.hours.hours < 0);       
}

short mostRecent(Time time1, Time time2) {
        if (time1.date.year > time2.date.year) return 1;
        if (time1.date.year < time2.date.year) return 0;
        if (time1.date.month > time2.date.month) return 1;
        if (time1.date.month < time2.date.month) return 0;
        if (time1.date.day > time2.date.day) return 1;
        if (time1.date.day < time2.date.day) return 0;
        if (time1.hours.hours > time2.hours.hours) return 1;
        if (time1.hours.hours < time2.hours.hours) return 0;
        if (time1.hours.minutes > time2.hours.minutes) return 1;
        if (time1.hours.minutes < time2.hours.minutes) return 0;
        return 0;
}

int timeDifference(Time entry, Time exit) {
        int totalMinutes = 0;
        
        totalMinutes += exit.hours.minutes - entry.hours.minutes;
        totalMinutes += (exit.hours.hours - entry.hours.hours) * 60;
        totalMinutes += (exit.date.day - entry.date.day) * 24 * 60;
        totalMinutes += (exit.date.year - entry.date.year) * 365 * 24 * 60;

        for (int i = entry.date.month; i < exit.date.month; i++) {
                totalMinutes += daysInTheMonth[i - 1] * 24 * 60;
        }
        return totalMinutes;
}

Date newDate(int day, int month, int year) {
        Date date;
        date.day = day;
        date.month = month;
        date.year = year;
        return date;
}

short equalDate(Date d0, Date d1) {
        return (d0.day == d1.day && d0.month == d1.month && d0.year == d1.year);
}

short mostRecentDate(Date d0, Date d1) {
        if (d0.year > d1.year) return 1;
        if (d0.year < d1.year) return 0;
        if (d0.month > d1.month) return 1;
        if (d0.month < d1.month) return 0;
        if (d0.day > d1.day) return 1;
        if (d0.day < d1.day) return 0;
        return 0;
}

short invalidDate(Date date) {
        return (date.month > 12 || date.month < 1 || 
                date.day < 1 || date.day > daysInTheMonth[date.month - 1]);
}