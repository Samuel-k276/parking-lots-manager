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
        putCar(*carMap, license, car);
    }
    
    addEntry(parkName, car, newTime);
    oneLessFreeSpot(park);
    changeTime(time, newTime);

    printf("%s %d\n", park->name, park->freeSpots);
}