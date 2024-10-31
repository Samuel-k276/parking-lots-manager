#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cars.h"

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

void addEntry (char *parkName, Car *thisCar, Time time) {
    Car car = *thisCar;
    History newHistory = createHistory(parkName, time);
    History current = car->history;
    if (car->history == NULL) {
        car->history = newHistory;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newHistory;
    }
    car->isParked = PARKED;  
}


void addExit(History *lastHistory, Car car, Time time) {
    History history = *lastHistory;
    history->exitTime = time;
    car->isParked = NOTPARKED;
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

char* licenseToString(char license[LICENSESIZE]) {
    char* string = (char*)malloc((LICENSESIZE + 2) * sizeof(char));
    string[0] = license[0];
    string[1] = license[1];
    string[2] = '-';
    string[3] = license[2];
    string[4] = license[3];
    string[5] = '-';
    string[6] = license[4];
    string[7] = license[5];
    string[8] = '\0';
    return string;
}


History lastHistory(Car car) {
    if (car == NULL) return NULL;
    if (car->history == NULL) return NULL;
    History current = car->history;
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

void printHistory(Car car) {
    History current = car->history;
    while (current != NULL) {
        printf("%s %02d-%02d-%04d %02d:%02d ", 
                current->parkName, current->entryTime.date.day, current->entryTime.date.month,
                current->entryTime.date.year, current->entryTime.hours.hours, current->entryTime.hours.minutes);
        if (current->exitTime.date.day != 0) {
            printf("%02d-%02d-%04d %02d:%02d", 
                current->exitTime.date.day, current->exitTime.date.month, current->exitTime.date.year,
                current->exitTime.hours.hours, current->exitTime.hours.minutes);
        }
        printf("\n");

        current = current->next;
    }
}

void freeCar(Car car) {
    freeHistory(car);
    free(car);
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