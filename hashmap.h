#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include "cars.h"

typedef struct Pair *Pair;
typedef struct HashMap *HashMap;

unsigned int hash(char key[LICENSESIZE]);
HashMap createCarHashMap();
void putCar(HashMap hashMap, char key[LICENSESIZE], Car value);
Car getCar(HashMap hashMap, char key[LICENSESIZE]);
void freeCarHashMap(HashMap hashMap);

#endif