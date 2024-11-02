#ifndef __PARKS_H__
#define __PARKS_H__

#include "time.h"
#include "cars.h"

typedef float PricesType;
typedef struct prices {
    PricesType x;
    PricesType y;
    PricesType z;
} Prices;

typedef struct billing {
    char license[LICENSESIZE];
    Hours hours;
    PricesType value;
    struct billing *next;
} *Billing;

typedef struct dailyBilling {
    Date date;
    PricesType value;
    Billing billList;
    struct dailyBilling *next;
} *DailyBilling;

typedef struct park {
    char* name;
    int capacity;
    int freeSpots;
    Prices prices;
    DailyBilling billing;
} *Park;

// Function declarations
short invalidCapacity(int capacidade);
short invalidCost(PricesType x, PricesType y, PricesType z);
short equalPark(Park park1, Park park2);
short isParkFull(Park park);

Park createPark(char *name, int capacity, 
                PricesType x, PricesType y, PricesType z);
Prices createPrices(PricesType x, PricesType y, PricesType z);

void oneLessFreeSpot(Park park);
void oneMoreFreeSpot(Park park);

PricesType calculateBilling(Prices prices, Time entryTime, Time exitTime);

void addToParkBilling(Park park, char license[LICENSESIZE], 
                    Time time, PricesType billed);
Billing newBilling(char license[LICENSESIZE], Hours hours, PricesType billed);
DailyBilling newDailyBilling(Billing firstBill, Date date);
DailyBilling getDailyBilling(Park park, Date date);

void printBilling(Park park);
void printDailyBilling(Park park, Date date);

void freePark(Park thisPark);

#endif
