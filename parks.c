#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parks.h"

Park createPark (char* name, int capacity, 
    PricesType x, PricesType y, PricesType z) {

    Park thisPark = (Park)malloc(sizeof(struct park));
    thisPark->name = (char *)name;
    thisPark->capacity = capacity;
    thisPark->freeSpots = capacity;
    thisPark->prices = createPrices(x, y, z);
    thisPark->billing = NULL;

    return thisPark;
}

Prices createPrices(PricesType x, PricesType y, PricesType z) {
    Prices thisPrices;
    thisPrices.x = x;
    thisPrices.y = y;
    thisPrices.z = z;

    return thisPrices;
}

short invalidCapacity (int capacidade) {
    return (capacidade <= 0);
}

short invalidCost (PricesType x, PricesType y, PricesType z) {
    return (x <= 0 || y <= 0 || z <= 0 || x >= y || y >= z);
}

short equalPark (Park park1, Park park2) {
    return (strcmp(park1->name, park2->name) == 0);
}

void oneLessFreeSpot (Park park) {
    park->freeSpots -= 1;
}

void oneMoreFreeSpot (Park park) {
    park->freeSpots += 1;
}

short isParkFull (Park park) {
    return park->freeSpots == 0;
}

void freePark(Park thisPark) {
    free(thisPark->name);
    while (thisPark->billing != NULL) {
        DailyBilling next = thisPark->billing->next;
        while (thisPark->billing->billList != NULL) {
            Billing nextBill = thisPark->billing->billList->next;
            free(thisPark->billing->billList);
            thisPark->billing->billList = nextBill;
        }
        free(thisPark->billing);
        thisPark->billing = next;
    }
    free(thisPark);
}

PricesType calculateBilling (Prices prices, Time entryTime, Time exitTime) {
    PricesType billing = 0, lastDayBilling = 0;
    int difference = timeDifference(entryTime, exitTime);
  
    while (difference > (60*24)) {
        billing += prices.z;
        difference -= (60*24);
    }  

    int count = 0;
    while (difference > 0 && count < 4) {
        lastDayBilling += prices.x;
        difference -= 15;
        count++;
    }

    while (difference > 0) {
        lastDayBilling += prices.y;
        difference -= 15;
    }

    if (lastDayBilling > prices.z) {
        lastDayBilling = prices.z;
    }

    billing += lastDayBilling;

    return billing;
}

void addToParkBilling(Park park, char license[LICENSESIZE], Time time,
    PricesType billed) {

    Billing billing = newBilling(license, time.hours, billed);

    if (park->billing == NULL) {
        DailyBilling new = newDailyBilling(billing, time.date);
        park->billing = new;
        return;
    }

    DailyBilling daily = getDailyBilling(park, time.date);

    if (daily == NULL) {
        DailyBilling new = newDailyBilling(billing, time.date);
        DailyBilling prev = NULL;
        daily = park->billing;
        while (daily != NULL) {
            prev = daily;
            daily = daily->next;
        }
        prev->next = new;
        return;
    }

    Billing bill = daily->billList;
    Billing prev = NULL;
    while (bill != NULL) {
        prev = bill;
        bill = bill->next;
    }
    prev->next = billing;
    daily->value += billed;    
}

Billing newBilling(char license[LICENSESIZE], Hours hours, PricesType billed) {
    Billing billing = (Billing)malloc(sizeof(struct billing));
    strcpy(billing->license, license);
    billing->hours = hours;
    billing->value = billed;
    billing->next = NULL;
    return billing;
}

DailyBilling newDailyBilling(Billing firstBill, Date date) {
    DailyBilling dailyBilling = (DailyBilling) malloc(
        sizeof(struct dailyBilling));
    dailyBilling->billList = firstBill;
    dailyBilling->date = date;
    dailyBilling->value = firstBill->value;
    dailyBilling->next = NULL;
    return dailyBilling;
}

DailyBilling getDailyBilling(Park park, Date date) {
    DailyBilling current = park->billing;
    while (current != NULL && !equalDate(current->date, date)) {
        current = current->next;
    }
    return current;
}


void printBilling(Park park) {
    DailyBilling current = park->billing;
    while (current != NULL) {
        printf("%02d-%02d-%04d %.2f\n", current->date.day, current->date.month,
                                        current->date.year, current->value);
        current = current->next;
    }
}

void printDailyBilling(Park park, Date date) {
    DailyBilling daily = getDailyBilling(park, date);
    if (daily == NULL) { return; }
    Billing current = daily->billList;
    while (current != NULL) {
        char *licenseString = licenseToString(current->license);
        printf("%s %02d:%02d %.2f\n", licenseString, current->hours.hours, 
                                      current->hours.minutes, current->value);

        free(licenseString);
        current = current->next;
    }
}