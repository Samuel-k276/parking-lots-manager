#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include "cars.h"

typedef struct Pair *Pair;
typedef struct HashMap *HashMap;

HashMap createHashMap();
void put(HashMap hashMap, char *key, Car value);
Car get(HashMap hashMap, char *key);
void removeKey(HashMap hashMap, char *key);
void freeHashMap(HashMap hashMap);

#endif