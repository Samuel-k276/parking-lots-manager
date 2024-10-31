#include <stdio.h>

#include "time.h"

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

//return 1 if time 1 is the most recent
short mostRecent (Time time1, Time time2) {
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

void changeTime (Time *dateToChange, Time newDate) {
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

int timeDifference (Time after, Time first) {
    int totalMinutes = 0;
    
    while (first.date.day != after.date.day || 
           first.date.month != after.date.month || 
           first.date.year != after.date.year) {
        
        totalMinutes += 24 * 60;

        first.date.day++;

        if (first.date.day > daysInTheMonth[first.date.month - 1]) {
            first.date.day = 1; 
            first.date.month++;  

            if (first.date.month > 12) {
                first.date.month = 1; 
                first.date.year++;     
            }
        }
    }

    totalMinutes += (after.hours.hours - first.hours.hours) * 60;
    totalMinutes += (after.hours.minutes - first.hours.minutes);

    return totalMinutes;
}

short daysDifference (Time first, Time after) {
    Time recent = first;
    Time old = after;
    short daysDifference;
    while (recent.date.month != old.date.month || recent.date.year != old.date.year) {
        daysDifference += daysInTheMonth[recent.date.month - 1];
        recent.date.month--;
        if (recent.date.month == 0) {
            recent.date.month = 12;
            recent.date.year--;
        }
    }

    return daysDifference;
}
