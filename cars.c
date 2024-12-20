#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cars.h"

Car createCar(char license[LICENSESIZE]) {
    Car thisCar = (Car)malloc(sizeof(struct carro));
    if (thisCar == NULL) {
        return NULL;
    }
    strcpy(thisCar->license, license);
    thisCar->history = NULL;
    thisCar->isParked = NOTPARKED;
    thisCar->faturacao = 0;

    return thisCar;
}

History createHistory(char *parkName, Time entryTime) {
    History thisHistory = (History)malloc(sizeof(struct carHistory));
    if (thisHistory == NULL) {
        return NULL;
    }
    thisHistory->entryTime = entryTime;
    thisHistory->exitTime = newTime(0, 0, 0, 0, 0);
    thisHistory->parkName = strdup(parkName);
    thisHistory->next = NULL;
    
    return thisHistory;
}

void addEntry(char *parkName, Car thisCar, Time time) {
    History newHistory = createHistory(parkName, time);

    if (newHistory == NULL) {
        return;
    }

    if (thisCar->history == NULL) {
        thisCar->history = newHistory;
    } else {
        History current = thisCar->history;
        History prev = NULL;

        while (current != NULL && strcmp(current->parkName, parkName) <= 0) {
            prev = current;
            current = current->next;
        }

        newHistory->next = current;
        if (prev == NULL) {
            thisCar->history = newHistory; 
        } else {
            prev->next = newHistory; 
        }
    }
    thisCar->isParked = PARKED; 
}

Time addExit(char *parkName, Car car, Time time) {
    History history = car->history;
    History prev = car->history;
    while (history != NULL && strcmp(history->parkName, parkName) <= 0) {
        prev = history;
        history = history->next;
    }
    prev->exitTime = time;
    car->isParked = NOTPARKED;
    return prev->entryTime;
}

short isParked(Car thisCar) {
    if (thisCar == NULL)    
        return NOTPARKED;
    return thisCar->isParked;
}

short invalidLicensePlate(char license[LICENSESIZE]) {
    if (invalidPair(license[0], license[1])
        || invalidPair(license[2], license[3])
        || invalidPair(license[4], license[5])) {
        return 1;
    }
    return (isupper(license[0]) &&isupper(license[2]) &&isupper(license[4])) ||
           (isdigit(license[0]) &&isdigit(license[2]) &&isdigit(license[4]));
}

short invalidPair(char a, char b) {
    return !(('0' <= a && a <= '9' && '0' <= b && b <= '9') ||
             ('A' <= a && a <= 'Z' && 'A' <= b && b <= 'Z'));
}

char* licenseToString(char license[LICENSESIZE]) {
    char* string = (char*)malloc((LICENSESIZE + 2) * sizeof(char));
    if (string == NULL) {
        return NULL;
    }
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

void printHistory(Car car) {
    History current = car->history;
    while (current != NULL) {
        Time entryTime = current->entryTime;
        printf("%s %02d-%02d-%04d %02d:%02d", current->parkName, 
            entryTime.date.day, entryTime.date.month, entryTime.date.year,
            entryTime.hours.hours, entryTime.hours.minutes);

        if (current->exitTime.date.day != 0) {
            Time exitTime = current->exitTime;
            printf(" %02d-%02d-%04d %02d:%02d", 
                exitTime.date.day, exitTime.date.month, exitTime.date.year,
                exitTime.hours.hours, exitTime.hours.minutes);
        }
        printf("\n");

        current = current->next;
    }
}

void removeCarHistory(char *name, Car car) {
    History current = car->history;
    History prev = NULL;
    while (current != NULL) {
        if (strcmp(current->parkName, name) == 0) {
            if (current->exitTime.date.day == 0) {
                car->isParked = NOTPARKED;
            }   
            if (prev == NULL) {
                car->history = current->next;
                free(current->parkName);
                free(current);
                current = car->history;
            } else {
                prev->next = current->next;
                free(current->parkName);
                free(current);
                current = prev->next;
            }

        } else {
            prev = current;
            current = current->next;
        }
    }
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

void freeCar(Car car) {
    if (car == NULL) {
        return;
    }
    
    freeHistory(car);
    free(car);
}
