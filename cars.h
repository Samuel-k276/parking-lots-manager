#ifndef __CARS_H__
#define __CARS_H__


typedef struct carro *Car;
typedef struct CarHistory *history;

//verifications
short isParked (Car thisCar);

//constructors
Car createCar (char license[6]);
void carEntry (Park AllParks, char *parkName, Car thisCar, DataEHora *ultimoRegisto);
void comandoE(Park AllParks, Car AllCars, DataEHora *ultimoRegisto);


#endif