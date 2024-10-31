#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parks.h"

Park createPark (char* name, int capacity, PricesType x, PricesType y, PricesType z) {
    Park thisPark = (Park)malloc(sizeof(struct park));
    thisPark->name = (char *)name;
    thisPark->capacity = capacity;
    thisPark->freeSpots = capacity;
    thisPark->prices = createPrices(x, y, z);
    thisPark->billing = 0;

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
    free(thisPark);
}

PricesType calculateBilling (Prices prices, Time entryTime, Time exitTime) {
    PricesType billing, lastDayBilling = 0;
    int difference = timeDifference(exitTime, entryTime);
    short lessThanDay = 0;
    

    while (difference > (60*24)) {
        billing += prices.z;
        difference -= (60*24);
    }

    if (difference < 24*60) {
        lessThanDay = 1;
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

    if (lessThanDay && lastDayBilling > prices.z) {
        lastDayBilling = prices.z;
    }

    billing += lastDayBilling;

    return billing;
}