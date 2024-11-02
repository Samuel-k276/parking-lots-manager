#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"

void commandP0(ListNode headNode) {
    printAllNodes(headNode);
}

void commandP1(ListNode *headNode, char* name, int capacity, PricesType x, 
               PricesType y, PricesType z) {
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

    if (tooManyParks(*headNode)) {
        printf("too many parks.\n");
        return;
    }
    
    Park newPark = createPark(name, capacity, x, y, z);
    appendListNode(createListNode(newPark), headNode);
}

void commandE(ListNode *headNode, HashMap *carMap, Time *time, char *parkName, 
              char license[LICENSESIZE], Time newTime) {
    Car car;
    ListNode node = findListNode(parkName, headNode);

    if (node == NULL || node->park == NULL) {
        printf("%s: no such parking.\n", parkName);
        return;
    }

    Park park = node->park;

    if (isParkFull(park)) {
        printf("%s: parking is full.\n", parkName);
        return;
    }

    if (invalidLicensePlate(license)) {
        printf("%c%c-%c%c-%c%c: invalid licence plate.\n", license[0], 
            license[1], license[2], license[3], license[4], license[5]);
        return;
    }

    if (isParked(car = getCar(*carMap, license))) {
        printf("%c%c-%c%c-%c%c: invalid vehicle entry.\n", license[0], 
            license[1], license[2], license[3], license[4], license[5]);
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
    
    addEntry(parkName, car, newTime);
    oneLessFreeSpot(park);
    changeTime(time, newTime);

    printf("%s %d\n", park->name, park->freeSpots);
}

void commandS(ListNode *headNode, HashMap *carMap, Time *time, char *parkName, 
              char license[LICENSESIZE], Time newTime) {
    Car car;
    ListNode node = findListNode(parkName, headNode);

    if (node == NULL) {
        printf("%s: no such parking.\n", parkName);
        return;
    }

    Park park = node->park;
    if (invalidLicensePlate(license)) {
        printf("%c%c-%c%c-%c%c: invalid licence plate.\n", license[0], 
            license[1], license[2], license[3], license[4], license[5]);
        return;
    }

    if (!isParked(car = getCar(*carMap, license))) {
        printf("%c%c-%c%c-%c%c: invalid vehicle exit.\n", license[0], 
            license[1], license[2], license[3], license[4], license[5]);
        return;
    }

    if (invalidTime(newTime) || mostRecent(*time, newTime)) {
        printf("invalid date.\n");
        return;
    }

    Time entryTime = addExit(parkName, car, newTime);
    oneMoreFreeSpot(park);
    PricesType billed = calculateBilling(park->prices, entryTime, newTime);
    addToParkBilling(park, license, newTime, billed);
    changeTime(time, newTime);
    char *licenseString = licenseToString(car->license);

    printf("%s %02d-%02d-%04d %02d:%02d %02d-%02d-%04d %02d:%02d %.2f\n", 
           licenseString, entryTime.date.day, entryTime.date.month, 
           entryTime.date.year, entryTime.hours.hours, entryTime.hours.minutes, 
           newTime.date.day, newTime.date.month, newTime.date.year, 
           newTime.hours.hours, newTime.hours.minutes, billed);   
    free(licenseString);
}

void commandV(HashMap carMap, char license[LICENSESIZE]) {
    if (invalidLicensePlate(license)) {
        char *licenseString = licenseToString(license);
        printf("%s: invalid licence plate.\n", licenseString);
        free(licenseString);
        return;
    }

    Car car = getCar(carMap, license);
    if (car == NULL || car->history == NULL) {
        char *licenseString = licenseToString(license);
        printf("%s: no entries found in any parking.\n", licenseString);
        free(licenseString);
        return;
    }

    printHistory(car);
}

void commandF0(ListNode headNode, char *name) {
    ListNode node = findListNode(name, &headNode);

    if (node == NULL) {
        printf("%s: no such parking.\n", name);
        return;
    }

    printBilling(node->park);
}

void commandF1(ListNode headNode, char *name, Date date, Date currentDate) {
    ListNode node = findListNode(name, &headNode);

    if (node == NULL) {
        printf("%s: no such parking.\n", name);
        return;
    }

    if (invalidDate(date) || mostRecentDate(date, currentDate)) {
        printf("invalid date.\n");
        return;
    }

    printDailyBilling(node->park, date);
}

void commandR(ListNode *headNode, char *name, HashMap *carMap) {
    ListNode node = findListNode(name, headNode);

    if (node == NULL) {
        printf("%s: no such parking.\n", name);
        return;
    }
    
    removeEntries(name, carMap);
    removeListNode(name, headNode);
    printListSorted(*headNode);
}

void printListSorted(ListNode headNode) {
    if (headNode == NULL) return;
    ListNode current = headNode;
    char *list[MAXPARKS] = {NULL};
    int count = 0;

    while (current != NULL) {
        int i = 0;
        char *name = current->park->name;
        while (i < count && strcmp(list[i], name) < 0) {
            i++;
        }
        for (int j = count; j > i; j--) {
            list[j] = list[j - 1];
        }
        list[i] = name;
        count++;
        current = current->next;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }
}