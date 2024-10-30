#ifndef __CARS_H__
#define __CARS_H__

typedef struct carro *Car;
typedef struct CarHistory *History;

//verifications
short isParked (Car thisCar);

//constructors
History createHistory (char *parkName, DataEHora entryTime);
void addHistory (History beginOfHistory, History historyToAdd);
Car createCar (char license[6]);
void addEntry (char *parkName, Car thisCar, DataEHora time);



#endif