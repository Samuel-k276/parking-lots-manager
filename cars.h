#ifndef __CARS_H__
#define __CARS_H__

#include "time.h"

#define LICENSESIZE 7
#define NOTPARKED 0
#define PARKED 1

typedef struct carHistory {
    Time entryTime;
    Time exitTime;
    char* parkName;
    struct carHistory *next;

} *History;
typedef struct carro {
    char license[LICENSESIZE];
    short isParked;
    History history;
    float faturacao;  
} *Car;


short isParked (Car thisCar);

//constructors
Car createCar (char license[LICENSESIZE]);
History createHistory (char *parkName, Time entryTime);
void addEntry (char *parkName, Car thisCar, Time time);
short invalidLicensePlate(char license[LICENSESIZE]);
short invalidPair (char a, char b);
char* licenseToString(char license[LICENSESIZE]);
void removeCarHistory(char *name, Car car);
void printHistory(Car car);
Time addExit(char *parkName, Car car, Time time);
void freeHistory(Car car);


#endif