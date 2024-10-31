#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"

void commandP0 (ListNode headNode) {
    printAllNodes(headNode);
}

void commandP1 (ListNode *headNode, char* name, int capacity, PricesType x, PricesType y, PricesType z) {
    if (nodeExists(name, *headNode)) {
        printf("%s: parking already exists.\n", name);
        return;
    }
    
    if (invalidCapacity(capacity)) {
        printf("%d: invalid capacity.\n", capacity);
        return;
    }

    if (invalidCost(x, y, z)) {
        printf("invalid cost.\n");
        return;
    }

    if (tooManyParks (*headNode)) {
        printf("too many parks.\n");
        return;
    }
    
    Park newPark = createPark(name, capacity, x, y, z);
    appendListNode(createListNode(newPark), headNode);
}

void commandE(ListNode *headNode, HashMap *carMap, Time *time, char *parkName, char license[LICENSESIZE], Time newTime) {
    Car car;
    ListNode node = findListNode(parkName, headNode);

    if (node == NULL) {
        printf("%s: no such parking.\n", parkName);
        return;
    }

    Park park = node->park;

    if (isParkFull(park)) {
        printf("%s: parking is full.\n", parkName);
        return;
    }

    if (invalidLicensePlate(license)) {
        printf("%c%c-%c%c-%c%c: invalid licence plate.\n", license[0], license[1], license[2], license[3], license[4], license[5]);
        return;
    }

    if (isParked(car = getCar(*carMap, license))) {
        printf("%c%c-%c%c-%c%c: invalid vehicle entry.\n", license[0], license[1], license[2], license[3], license[4], license[5]);
        return;
    }

    if (invalidTime(newTime) || mostRecent(*time, newTime)) {
        printf("invalid date.\n");
        return;
    }

    if (car == NULL) {
        car = createCar(license);
        putCar(carMap, license, car);
    }
    
    addEntry(parkName, &car, newTime);
    oneLessFreeSpot(park);
    changeTime(time, newTime);

    printf("%s %d\n", park->name, park->freeSpots);
}

void commandS(ListNode *headNode, HashMap *carMap, Time *time, char *parkName, char license[LICENSESIZE], Time newTime) {
    Car car;
    History lastHistoryOfCar;
    ListNode node = findListNode(parkName, headNode);

    if (node == NULL) {
        printf("%s: no such parking.\n", parkName);
        return;
    }

    Park park = node->park;
    if (invalidLicensePlate(license)) {
        printf("%c%c-%c%c-%c%c: invalid licence plate.\n", license[0], license[1], license[2], license[3], license[4], license[5]);
        return;
    }

    if (!isParked(car = getCar(*carMap, license))) {
        printf("%c%c-%c%c-%c%c: invalid vehicle exit.\n", license[0], license[1], license[2], license[3], license[4], license[5]);
        return;
    }

    lastHistoryOfCar = lastHistory(car);

    if (invalidTime(newTime) || mostRecent(*time, newTime)) {
        printf("invalid date.\n");
        return;
    }

    addExit(&lastHistoryOfCar, car, newTime);
    oneMoreFreeSpot(park);
    changeTime(time, newTime);
    char *licenseString = licenseToString(car->license);
    printf("%s %02d-%02d-%04d %02d:%02d %02d-%02d-%04d %02d:%02d %.2f\n", licenseString, lastHistoryOfCar->entryTime.date.day, 
                                                    lastHistoryOfCar->entryTime.date.month, lastHistoryOfCar->entryTime.date.year, 
                                                    lastHistoryOfCar->entryTime.hours.hours, lastHistoryOfCar->entryTime.hours.minutes, 
                                                    newTime.date.day, newTime.date.month, newTime.date.year, newTime.hours.hours, newTime.hours.minutes,
                                                    calculateBilling(park->prices, lastHistoryOfCar->entryTime, newTime));   
    free(licenseString);
}


void commandV(HashMap carMap, char license[LICENSESIZE]) {
    Car car;

    if (invalidLicensePlate(license)) {
        printf("%c%c-%c%c-%c%c: invalid licence plate.\n", license[0], license[1], license[2], license[3], license[4], license[5]);
        return;
    }

    car = getCar(carMap, license);
    if (car == NULL) {
        printf("%c%c-%c%c-%c%c: no entries found in any parking.\n", license[0], license[1], license[2], license[3], license[4], license[5]);
        return;
    }

    printHistory(car);
}