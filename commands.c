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

short validateEntry(ListNode node, char *parkName, HashMap *carMap, 
                    char license[LICENSESIZE], Time *time, Time newTime) {
    if (node == NULL) {
        printf("%s: no such parking.\n", parkName);
        return 0;
    }

    if (isParkFull(node->park)) {
        printf("%s: parking is full.\n", parkName);
        return 0;
    }

    if (invalidLicensePlate(license)) {
        printf("%c%c-%c%c-%c%c: invalid licence plate.\n", license[0], 
            license[1], license[2], license[3], license[4], license[5]);
        return 0;
    }

    if (isParked(getCar(*carMap, license))) {
        printf("%c%c-%c%c-%c%c: invalid vehicle entry.\n", license[0], 
            license[1], license[2], license[3], license[4], license[5]);
        return 0;
    }

    if (invalidTime(newTime) || mostRecent(*time, newTime)) {
        printf("invalid date.\n");
        return 0;
    }

    return 1;
}

void commandE(ListNode *headNode, HashMap *carMap, Time *time, char *parkName, 
              char license[LICENSESIZE], Time newTime) {
    ListNode node = findListNode(parkName, headNode);

    if (!validateEntry(node, parkName, carMap, license, time, newTime)) {
        return;
    }

    Car car = getCar(*carMap, license);
    if (car == NULL) {
        car = createCar(license);
        putCar(carMap, license, car);
    }
    
    addEntry(parkName, car, newTime);
    oneLessFreeSpot(node->park);
    changeTime(time, newTime);

    printf("%s %d\n", parkName, node->park->freeSpots);
}

short validateExit(ListNode node, char *parkName, HashMap *carMap, 
                   char license[LICENSESIZE], Time *time, Time newTime) {
    if (node == NULL) {
        printf("%s: no such parking.\n", parkName);
        return 0;
    }

    if (invalidLicensePlate(license)) {
        printf("%c%c-%c%c-%c%c: invalid licence plate.\n", license[0], 
            license[1], license[2], license[3], license[4], license[5]);
        return 0;
    }

    if (!isParked(getCar(*carMap, license))) {
        printf("%c%c-%c%c-%c%c: invalid vehicle exit.\n", license[0], 
            license[1], license[2], license[3], license[4], license[5]);
        return 0;
    }

    if (invalidTime(newTime) || mostRecent(*time, newTime)) {
        printf("invalid date.\n");
        return 0;
    }

    return 1;
}

void commandS(ListNode *headNode, HashMap *carMap, Time *time, char *parkName, 
              char license[LICENSESIZE], Time newT) {
    ListNode node = findListNode(parkName, headNode);

    if (!validateExit(node, parkName, carMap, license, time, newT)) {
        return;
    }

    Park park = node->park;
    Car car = getCar(*carMap, license);

    Time entryT = addExit(parkName, car, newT);
    oneMoreFreeSpot(park);
    PricesType billed = calculateBilling(park->prices, entryT, newT);
    addToParkBilling(park, license, newT, billed);
    changeTime(time, newT);
    char *licenseString = licenseToString(car->license);

    printf("%s %02d-%02d-%04d %02d:%02d %02d-%02d-%04d %02d:%02d %.2f\n", 
    licenseString, entryT.date.day, entryT.date.month, entryT.date.year, 
    entryT.hours.hours, entryT.hours.minutes, newT.date.day, newT.date.month,
    newT.date.year, newT.hours.hours, newT.hours.minutes, billed);   
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