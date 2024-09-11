#ifndef __PARKS_H__
#define __PARKS_H__

typedef struct park *Park;
typedef struct precos Precos;
typedef float TipoPrecos;

//verifications
short invalidCapacity (int capacidade);
short invalidCost (TipoPrecos x, TipoPrecos y, TipoPrecos z);
short parkingAlreadyExists (const char *name, Park beginOfList);
short tooManyParks (Park beginOfList);

//secondary
char *lernome();

//constructors
Park createPark (const char *name, int capacity, TipoPrecos x, TipoPrecos y, TipoPrecos z);
void addPark (Park park, Park beginOfList);
void commandP (Park beginOfList);

//destructor
void freePark (Park thisPark);
void deletePark(const char* name, Park beginOfList);

#endif