#ifndef __CARS_H__
#define __CARS_H__

typedef struct carro *Car;
typedef struct carHistory *History;

#define LICENSESIZE 7
#define NOTPARKED 0
#define PARKED 1

#include "time.h"
#include "time.c"

short isParked (Car thisCar);

//constructors
History createHistory (char *parkName, Time entryTime);
void addHistory (History beginOfHistory, History historyToAdd);
Car createCar (char license[LICENSESIZE]);
void addEntry (char *parkName, Car thisCar, Time time);
short invalidLicensePlate(char license[LICENSESIZE]);
void freeHistory(Car car);


#endif