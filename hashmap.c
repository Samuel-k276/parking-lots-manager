#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cars.h"
#include "cars.c"
#include "hashmap.h"

#define HASHSIZE 101

struct Pair {
    char key[LICENSESIZE];
    Car value;
    struct Pair *next;
};

struct HashMap {
    Pair table[HASHSIZE];
};

unsigned int hash(char key[LICENSESIZE]) {
    unsigned long int hashval = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashval = key[i] + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

HashMap createCarHashMap() {
    HashMap hashMap = (HashMap *) malloc(sizeof(HashMap));
    for (int i = 0; i < HASHSIZE; i++) {
        hashMap->table[i] = NULL;
    }
    return hashMap;
}

void putCar(HashMap hashMap, char key[LICENSESIZE], Car value) {
    unsigned int hashval = hash(key);
    Pair pair = hashMap->table[hashval];

    while (pair != NULL) {
        pair = pair->next;
    }

    pair = (Pair *) malloc(sizeof(Pair));
    strcpy(pair->key, key);
    pair->value = value;
    pair->next = hashMap->table[hashval];
    hashMap->table[hashval] = pair;
}

Car getCar(HashMap hashMap, char key[LICENSESIZE]) {
    unsigned int hashval = hash(key);
    Pair pair = hashMap->table[hashval];

    while (pair != NULL) {
        if (strcmp(pair->key, key) == 0) {
            return pair->value;
        }
        pair = pair->next;
    }

    return NULL;
}


void freeCarHashMap(HashMap map) {
    for (int i = 0; i < HASHSIZE; i++) {
        Pair pair = map->table[i];
        while (pair != NULL) {
            Pair next = pair->next;
            free(pair->key);
            free(pair);
            pair = next;
        }
    }
    for (int i = 0; i < HASHSIZE; i++) {
        freeHistory(map->table[i]->value);
    }
    
    free(map->table);
    free(map);
}