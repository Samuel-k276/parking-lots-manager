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
Car createCar (char license[LICENSESIZE]);
History createHistory (char *parkName, Time entryTime);
void addHistory (History beginOfHistory, History historyToAdd);
void addEntry (char *parkName, Car thisCar, Time time);
short invalidLicensePlate(char license[LICENSESIZE]);
short invalidPair (char a, char b);
void freeHistory(Car car);


#endif