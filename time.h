#ifndef __TIME_H__
#define __TIME_H__


typedef struct hours Hours;
typedef struct date Date;
typedef struct time Time;


Time time0 ();
void changeTime (Time *dateToChange, Time newDate);


short invalidTime (Time date);
short mostRecent (Time data1, Time data2);


int timeDiference (Time recent, Time old);
short daysDifference (Time recent, Time old);

#endif
