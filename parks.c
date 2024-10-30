#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parks.h"

struct prices {
    PricesType x;
    PricesType y;
    PricesType z;
};

struct park {
    char* name;
    int capacity;
    int freeSpots;
    Prices prices;
    PricesType billing;
};

Park createPark (const char* name, int capacity, PricesType x, PricesType y, PricesType z) {
    Park thisPark = (Park)malloc(sizeof(struct park));

    strcpy(thisPark->name, name);
    thisPark->capacity = thisPark->freeSpots = capacity;
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

short isParkFull (Park park) {
    return park->freeSpots == 0;
}

void freePark(Park thisPark) {
    free(thisPark->name);
    free(thisPark);
}

