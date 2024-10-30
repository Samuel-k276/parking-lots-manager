#ifndef __PARKS_H__
#define __PARKS_H__

typedef struct park *Park;
typedef struct prices Prices;
typedef float PricesType;

//verifications
short invalidCapacity (int capacidade);
short invalidCost (PricesType x, PricesType y, PricesType z);
short parkingAlreadyExists (const char *name, Park beginOfList);
short tooManyParks (Park beginOfList);
short noSuchPark (Park beginOfList, const char* nameToFind);

//constructors
Park createPark (const char *name, int capacity, PricesType x, PricesType y, PricesType z);
void addPark (Park park, Park beginOfList);

//setters
void oneLessFreeSpot (Park beginOfList, const char* parkName);

//getters
Park findPark (Park beginOfList, const char* nameToFind);

//destructor
void freePark (Park thisPark);
void deletePark(const char* name, Park beginOfList);

#endif