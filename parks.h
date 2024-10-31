#ifndef __PARKS_H__
#define __PARKS_H__

typedef struct park *Park;
typedef struct prices Prices;
typedef float PricesType;

short invalidCapacity (int capacidade);
short invalidCost (PricesType x, PricesType y, PricesType z);
short equalPark (Park park1, Park park2);

Park createPark (char *name, int capacity, PricesType x, PricesType y, PricesType z);
Prices createPrices(PricesType x, PricesType y, PricesType z);

void oneLessFreeSpot (Park park);
short isParkFull (Park park);

void freePark (Park thisPark);

#endif