#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    thisHistory->parkName = parkName;
    
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
    if (invalidPair(license[0], license[1])
        || invalidPair(license[2], license[3])
        || invalidPair(license[4], license[5])) {
        return 1;
    }
    return (isupper(license[0]) && isupper(license[2]) && isupper(license[4])) ||
           (isdigit(license[0]) && isdigit(license[2]) && isdigit(license[4]));
}

short invalidPair (char a, char b) {
    return !('0' <= a <= '9' && '0' <= b <= '9' ||
             'A' <= a <= 'Z' && 'A' <= b <= 'Z' );

}
void freeHistory(Car car) {
    History current = car->history;
    History next;

    while (current != NULL) {
        next = current->next;
        free(current->parkName);
        free(current);
        current = next;
    }
    
}