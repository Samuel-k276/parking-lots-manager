#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"

void commandP0 (ListNode headNode) {
    printAllNodes(headNode);
}

void commandP1 (ListNode headNode, char* name, int capacity, PricesType x, PricesType y, PricesType z) {
    if (nodeExists(name, headNode)) {
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

    if (tooManyParks (headNode)) {
        printf("too many parks.\n");
        return;
    }

    Park newPark = createPark(name, capacity, x, y, z);
    free(name);
    appendListNode(createListNode(newPark), headNode);
}

void comandoE(ListNode headNode, HashMap carMap, Time *time, char *parkName, char license[LICENSESIZE], Time newTime) {
    Car car;
    Park park = findListNode(parkName, headNode)->park;

    if (park == NULL) {
        printf("%s: no such parking.\n", parkName);
        return;
    }

    if (isParkFull(park)) {
        printf("%s: parking is full.\n", parkName);
        return;
    }

    if (invalidLicensePlate(license)) {
        printf("%s: invalid licence plate.\n", license);
        return;
    }

    if (isParked(car = getCar(carMap, license))) {
        printf("%s: invalid vehicle entry.\n", license);
        return;
    }

    if (car == NULL) {
        car = createCar(license);
        putCar(carMap, license, car);
    }
    
    addEntry(parkName, car, newTime);
    oneLessFreeSpot(park);
    changeTime(time, newTime);
}