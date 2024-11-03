/**
 * @file cars.h
 * @brief Header file for managing car parking information and history.
 *
 * This file contains the definitions and function declarations for managing
 * car parking information, including car creation, history management, and
 * various utility functions.
 */ 
#ifndef __CARS_H__
#define __CARS_H__

#include "time.h"

/** The size of the license plate */
#define LICENSESIZE 7

/** The car is not parked */
#define NOTPARKED 0

/** The car is parked */
#define PARKED 1

/**
 * @brief Structure representing the history of a car's parking.
 *
 * This structure holds information about a car's entry and exit times,
 * the name of the parking lot, and a pointer to the next history record.
 */
typedef struct carHistory {
    Time entryTime;
    Time exitTime;
    char* parkName;
    struct carHistory *next;

} *History;

/**
 * @brief Structure representing a car.
 *
 * This structure holds information about a car, including its license plate,
 * parking status, history, and total earnings.
 */
typedef struct carro {
    char license[LICENSESIZE];
    short isParked;
    History history;
    float faturacao;  
} *Car;

/**
 * @brief Creates a new car with the given license plate.
 *
 * @param license The license plate of the car.
 * @return The newly created car.
 */
Car createCar(char license[LICENSESIZE]);

/**
 * @brief Creates a new history record for a car.
 *
 * @param parkName The name of the parking lot.
 * @param entryTime The entry time of the car.
 * @return The newly created history record.
 */
History createHistory(char *parkName, Time entryTime);

/**
 * @brief Adds an entry record to the car's history.
 *
 * @param parkName The name of the parking lot.
 * @param thisCar The car to which the entry record is added.
 * @param time The entry time of the car.
 */
void addEntry(char *parkName, Car thisCar, Time time);

/**
 * @brief Adds an exit record to the car's history.
 *
 * @param parkName The name of the parking lot.
 * @param car The car to which the exit record is added.
 * @param time The exit time of the car.
 * @return The time spent in the parking lot.
 */
Time addExit(char *parkName, Car car, Time time);


/**
 * @brief Checks if the car is currently parked.
 *
 * @param thisCar The car to check.
 * @return 1 if the car is parked, 0 otherwise.
 */
short isParked(Car thisCar);

/**
 * @brief Checks if the given license plate is invalid.
 *
 * @param license The license plate to check.
 * @return 1 if the license plate is invalid, 0 otherwise.
 */
short invalidLicensePlate(char license[LICENSESIZE]);

/**
 * @brief Checks if the given pair of characters is invalid.
 *
 * @param a The first character.
 * @param b The second character.
 * @return 1 if the pair is invalid, 0 otherwise.
 */
short invalidPair(char a, char b);

/**
 * @brief Converts the license plate to a string.
 *
 * @param license The license plate to convert.
 * @return A string representation of the license plate.
 */
char* licenseToString(char license[LICENSESIZE]);

/**
 * @brief Prints the history of a car.
 *
 * @param car The car whose history is to be printed.
 */
void printHistory(Car car);

/**
 * @brief Removes the history of a car for a given parking lot.
 *
 * @param name The name of the parking lot.
 * @param car The car whose history is to be removed.
 */
void removeCarHistory(char *name, Car car);

/**
 * @brief Frees the memory allocated for the history of a car.
 *
 * @param car The car whose history is to be freed.
 */
void freeHistory(Car car);

/**
 * @brief Frees the memory allocated for the car.
 *
 * @param car The car to be freed.
 */
void freeCar(Car car);

#endif