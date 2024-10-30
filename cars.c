#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cars.h"

struct carro {
    char license[LICENSESIZE];
    short isParked;
    History history;
    float faturacao;  
};


struct carHistory {
    Time entryTime;
    Time exitTime;
    char* parkName;
    History next;
};

Car createCar (char license[LICENSESIZE]) {
    Car thisCar = (Car)malloc(sizeof(struct carro));
    strcpy(thisCar->license, license);
    thisCar->isParked = NOTPARKED;
    thisCar->faturacao = 0;

    return thisCar;
}

short isParked (Car thisCar) {
    if (thisCar == NULL)    
        return NOTPARKED;
    return thisCar->isParked;
}

History createHistory (char *parkName, Time entryTime) {
    History thisHistory = (History)malloc(sizeof(struct carHistory));
    thisHistory->entryTime = entryTime;
    strcpy(thisHistory->parkName, parkName);
    
    return thisHistory;
}

void addHistory (History beginOfHistory, History historyToAdd) {
    History current = beginOfHistory;
    if (beginOfHistory == NULL) {
        beginOfHistory = historyToAdd;
        return;
    }

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = historyToAdd;
}

void addEntry (char *parkName, Car thisCar, Time time) {
    History newHistory = createHistory(parkName, time);
    addHistory(thisCar->history, newHistory);
    thisCar->isParked = PARKED;  
}


void addExit(char *parkName, Car thisCar, Time time) {
    

    thisCar->isParked = NOTPARKED;
}

short invalidLicensePlate(char license[LICENSESIZE]) {
    return 1;
}

void freeHistory(Car car) {
    
}