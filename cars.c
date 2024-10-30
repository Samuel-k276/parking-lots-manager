#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cars.h"
#include "parks.h"
#include "time.h"
#include "time.c"

#define LICENSESIZE 7
#define NOTPARKED 0
#define PARKED 1

struct carro {
    char license[LICENSESIZE];
    short isParked;
    History history;
    PricesType faturacao;  
};


struct CarHistory {
    Time entryTime;
    Time exitTime;
    const char* parkName;
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
    return thisCar->isParked;
}

History createHistory (char *parkName, Time entryTime) {
    History thisHistory = (History)malloc(sizeof(struct CarHistory));
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