/**
 * @file hashmap.h
 * @brief This file contains the definitions and function declarations for
 * managing hash maps, including creation, insertion, retrieval, and deletion 
 * of key-value pairs.
 * 
 * This file is part of the parking lots manager application, which is a simple
 * application for managing parking lots and cars parked in them.
 */

#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include "cars.h"

/** The size of the hash table */
#define HASHSIZE 101

/**
 * @brief Structure representing a pair of key and value.
 *
 * This structure holds a key and a value, 
 * as well as a pointer to the next pair.
 */
typedef struct Pair {
    char key[LICENSESIZE];
    Car value;
    struct Pair *next;
} *Pair;

/**
 * @brief Structure representing a hash map.
 *
 * This structure holds an array of pairs, each containing a key and a value.
 */
typedef struct HashMap {
    Pair table[HASHSIZE];
} *HashMap;

/**
 * @brief Creates a new hash map.
 *
 * @return The newly created hash map.
 */
HashMap createCarHashMap();

/**
 * @brief Hashes a key.
 *
 * @param key The key to hash.
 * @return The hash value of the key.
 */
unsigned int hash(char key[LICENSESIZE]);

/**
 * @brief Puts a car in the hash map.
 *
 * @param hashMap The hash map to put the car in.
 * @param key The key of the car.
 * @param value The car to put in the hash map.
 */
void putCar(HashMap *hashMap, char key[LICENSESIZE], Car value);

/**
 * @brief Gets a car from the hash map.
 *
 * @param hashMap The hash map to get the car from.
 * @param key The key of the car.
 * @return The car with the given key.
 */
Car getCar(HashMap hashMap, char key[LICENSESIZE]);

/**
 * @brief Removes a car from the hash map.
 *
 * @param hashMap The hash map to remove the car from.
 * @param key The key of the car.
 */
void removeEntries(char *name, HashMap *carMap);

/**
 * @brief Frees the memory allocated for the hash map.
 *
 * @param hashMap The hash map to free.
 */
void freeCarHashMap(HashMap *hashMap);

#endif