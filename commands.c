#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parks.h"
#include "parks.c"
#include "cars.h"
#include "cars.c"
#include "time.h"
#include "time.c"
#include "hashmap.h"
#include "hashmap.c"
#include "linkedList.h"
#include "linkedList.c"

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
    appendListNode(newPark, headNode);
}

void comandoE(ListNode headNode, HashMap carMap, Time *time, char *parkName, char license[LICENSESIZE], Time newTime) {
    Car car;
    Park park = findListNode(parkName, headNode);

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
    
    carEntry(parkName, car, time);
    oneLessFreeSpot(park);
    changeDate(time, newTime);
}