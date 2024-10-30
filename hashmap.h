#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include "cars.h"

typedef struct Pair *Pair;
typedef struct HashMap *HashMap;

unsigned int hash(char key[LICENSESIZE]);
HashMap createHashMap();
void put(HashMap hashMap, char key[LICENSESIZE], Car value);
Car get(HashMap hashMap, char key[LICENSESIZE]);
void freeHashMap(HashMap hashMap);

#endif