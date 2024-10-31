#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include "cars.h"

#define HASHSIZE 101

typedef struct Pair {
    char key[LICENSESIZE];
    Car value;
    struct Pair *next;
} *Pair;

typedef struct HashMap {
    Pair table[HASHSIZE];
} *HashMap;

unsigned int hash(char key[LICENSESIZE]);
HashMap createCarHashMap();
void putCar(HashMap *hashMap, char key[LICENSESIZE], Car value);
Car getCar(HashMap hashMap, char key[LICENSESIZE]);
void freeCarHashMap(HashMap hashMap);

#endif