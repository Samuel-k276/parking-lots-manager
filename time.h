#ifndef __TIME_H__
#define __TIME_H__

typedef struct hours {
    int hours;
    int minutes;
} Hours;

typedef struct date {
    int day;
    int month;
    int year;
} Date;

typedef struct time {
    Date date;
    Hours hours;
} Time;

Time time0 ();
void changeTime (Time *dateToChange, Time newDate);
Time newTime(int day, int month, int year, int hours, int minutes);

short invalidTime (Time date);
short mostRecent (Time data1, Time data2);

int timeDifference (Time recent, Time old);

Date newDate(int day, int month, int year);
short equalDate(Date d0, Date d1);
short mostRecentDate(Date d0, Date d1);
short invalidDate(Date date);

#endif
