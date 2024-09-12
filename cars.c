#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parks.h"
#include "cars.h"
#include "data.h"
#include "data.c"

#define LICENSESIZE 7
#define PARKED 1

struct carro {
    char license[LICENSESIZE];
    short isParked;
    History history;
    TipoPrecos faturacao;  

    Car next;    
};


struct CarHistory {
    DataEHora entryTime;
    DataEHora exitTime;
    const char* parkName;

    History next;
};

short carExists (Car AllCars, char license[6]) {
    Car current = AllCars;
    while (current != NULL) {
        if (!strcmp(license, current->license)) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

short isParked (Car thisCar) {
    return thisCar->isParked;
}

Car findCar (Car AllCars, char license[6]) {
    Car current =  AllCars;
    while (strcmp(current->license, license)) {
        current = current->next;
    }
    return current;
}

History findHistory (History firstRegist) {
    History current = firstRegist;
    while (current != NULL && current->exitTime.data.ano != NULL) {
        current = current->next;
    }
    return current;
}

Car createCar (char license[6]) {
    Car thisCar = (Car)malloc(sizeof(struct carro));
    strcpy(thisCar->license, license);
    thisCar->isParked = 0;
    thisCar->faturacao = 0;

    return thisCar;
}

void carEntry (Park AllParks, char *parkName, Car thisCar, DataEHora time) {
    Park thisPark = findPark(AllParks, parkName);
    History newHistoric = findHistory()
    thisCar->isParked = PARKED;
    

}



void comandoE(Park AllParks, Car AllCars, DataEHora *ultimoRegisto) {
    DataEHora time;
    char license[LICENSESIZE], l1[3], l2[3], l3[3];
    const char *parkName = lernome();

    scanf("%s-%s-%s %d-%d-%d %d:%d", l1, l2, l3, &time.data.dia, &time.data.mes, &time.data.dia, &time.hora.horas, &time.hora.minutos);
    strcpy(license, l1);
    strcat(license, l2);
    strcat(license, l3);

    if (noSuchPark(AllParks, parkName)) {

        return;
    }

    Car thisCar;
    if (carExists(AllCars, license)) {
        thisCar = findCar(AllCars, license);
    } else {
        thisCar = createCar(license);
    }

    if (isParked(thisCar)) {

        return;
    }
    
    carEntry(AllParks, parkName, thisCar, time);
    changeDate(ultimoRegisto, time);
}