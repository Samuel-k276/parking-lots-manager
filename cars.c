#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parks.h"
#include "cars.h"
#include "data.h"
#include "data.c"

#define LICENSESIZE 6
#define PARKED 1

struct carro {
    char license[LICENSESIZE];
    short isParked;
    history history;
    TipoPrecos faturacao;  

    Car next;    
};


struct CarHistory {
    DataEHora entryTime;
    DataEHora exitTime;
    const char* parkName;

    history next;
};

short isParked (Car thisCar) {
    return thisCar->isParked;
}

Car createCar (char license[6]) {
    Car thisCar = (Car)malloc(sizeof(struct carro));
    strcpy(thisCar->license, license);
    thisCar->isParked = 0;
    thisCar->faturacao = 0;

    return thisCar;
}

void carEntry (char *parkName, Car thisCar, DataEHora *ultimoRegisto) {


}



void comandoE(Park AllParks, Car AllCars, DataEHora *ultimoRegisto) {
    
}