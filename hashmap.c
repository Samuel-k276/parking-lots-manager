#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

HashMap createCarHashMap() {
    HashMap hashMap = (HashMap) malloc(sizeof(struct HashMap));
    if (hashMap == NULL) {
        perror("error creating hashmap");
        return NULL;
    }
    for (int i = 0; i < HASHSIZE; i++) {
        hashMap->table[i] = NULL;
    }
    return hashMap;
}

unsigned int hash(char key[LICENSESIZE]) {
    unsigned long int hashval = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashval = key[i] + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

void putCar(HashMap *hashMap, char key[LICENSESIZE], Car value) {
    if (*hashMap == NULL) {
        perror("hashmap is NULL");
        return;
    }

    if (value == NULL) {
        perror("car is NULL");
        return;
    }

    unsigned int hashval = hash(key);
    HashMap carMap = *hashMap;
    Pair pair = carMap->table[hashval];

    while (pair != NULL)
        pair = pair->next;

    pair = (Pair) malloc(sizeof(struct Pair));
    if (pair == NULL) {
        perror("error creating pair");
        return;
    }
    strcpy(pair->key, key);
    pair->value = value;
    pair->next = carMap->table[hashval];
    carMap->table[hashval] = pair;
}

Car getCar(HashMap hashMap, char key[LICENSESIZE]) {
    if (hashMap == NULL) {
        perror("hashmap is NULL");
        return NULL;
    };
    unsigned int hashval = hash(key);
    Pair pair = hashMap->table[hashval];

    while (pair != NULL) {
        if (strcmp(pair->key, key) == 0)
            return pair->value;
        pair = pair->next;
    }

    return NULL;
}

void removeEntries(char *name, HashMap *carMap) {
    if (*carMap == NULL) return;

    HashMap carHashMap = *carMap;
    for (int i = 0; i < HASHSIZE; i++) {
        Pair pair = carHashMap->table[i];
        while (pair != NULL) {
            if (pair->value != NULL) 
                removeCarHistory(name, pair->value);
            pair = pair->next;
        }
    }
}

void freeCarHashMap(HashMap *map) {
    if (*map == NULL) return; // Certifique-se de que não é NULL

    for (int i = 0; i < HASHSIZE; i++) {
        Pair pair = (*map)->table[i];
        while (pair != NULL) {
            Pair next = pair->next;
            if (pair->value != NULL) {
                freeCar(pair->value); // Libere campos internos de Car
            }
            free(pair); // Libera o par
            pair = next;
        }
    }
    free(*map);   // Libera o hashmap
    *map = NULL;  // Define como NULL para evitar ponteiros pendentes
}
