#include <stdio.h>

#include "time.h"

struct hours {
    int hours;
    int minutes;
};

struct date {
    int day;
    int month;
    int year;
};

struct time {
    Date date;
    Hours hours;
};

const short daysInTheMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Time time0() {
  Time time;
  time.date.day = 1;
  time.date.month = 1;
  time.date.year = 1;
  time.hours.hours = 0;
  time.hours.minutes = 0;
 
  return time;
}

short invalidTime(Time date) {
        return (date.date.month > 12 || date.date.month < 1 || date.date.day < 1 || date.date.day > daysInTheMonth[date.date.month - 1] || 
            date.hours.minutes > 59 || date.hours.minutes < 0 || date.hours.hours > 23 || date.hours.hours < 0);       
}

//return 1 if date 1 is the most recent
short mostRecent (Time time0, Time time1) {
    if (time0.date.year > time1.date.year) return 1;
    if (time0.date.year < time1.date.year) return 0;
    if (time0.date.month > time1.date.month) return 1;
    if (time0.date.month < time1.date.month) return 0;
    if (time0.date.day > time1.date.day) return 1;
    if (time0.date.day < time1.date.day) return 0;
    if (time0.hours.hours > time1.hours.hours) return 1;
    if (time0.hours.hours < time1.hours.hours) return 0;
    if (time0.hours.minutes > time1.hours.minutes) return 1;
    if (time0.hours.minutes < time1.hours.minutes) return 0;
    return 0;
}

void changeTime (Time *dateToChange, Time newDate) {
    free(dateToChange);
    dateToChange = &newDate;
}

int timeDiference (Time recent, Time old) {
    short days;
    if (old.date.month > recent.date.month) {
        days = -1*daysDifference(old, recent);
    } else {
        days = daysDifference(recent, old);
    }

    while (recent.date.month != old.date.month) {
        recent.date.month -= 1;
    }

    return ((recent.hours.minutes - old.hours.minutes) + (recent.hours.hours - old.hours.hours)*60 +
            ((recent.date.year - old.date.year)*365 + days)*24*60);
}

short daysDifference (Time recent, Time old) {
    short daysDifference;
    while (recent.date.month != old.date.month) {
        recent.date.month -= 1;
        daysDifference += daysInTheMonth[recent.date.month];
    }
    return daysDifference;
}
