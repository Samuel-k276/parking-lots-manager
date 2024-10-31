#ifndef __PARKS_H__
#define __PARKS_H__

#include "time.h"

typedef float PricesType;
typedef struct prices {
    PricesType x;
    PricesType y;
    PricesType z;
} Prices;

typedef struct park {
    char* name;
    int capacity;
    int freeSpots;
    Prices prices;
    PricesType billing;
} *Park;


short invalidCapacity (int capacidade);
short invalidCost (PricesType x, PricesType y, PricesType z);
short equalPark (Park park1, Park park2);

Park createPark (char *name, int capacity, PricesType x, PricesType y, PricesType z);
Prices createPrices(PricesType x, PricesType y, PricesType z);

void oneLessFreeSpot (Park park);
void oneMoreFreeSpot (Park park);
short isParkFull (Park park);
PricesType calculateBilling (Prices prices, Time entryTime, Time exitTime);

void freePark (Park thisPark);

#endif