/**
 * @file parks.h
 * @brief This file contains the definitions and function declarations for 
 * managing parking lots, including creation, billing, and various utility 
 * functions.
 * 
 * This file is part of the parking lots manager application, which is a simple
 * application for managing parking lots and cars parked in them.
 */
#ifndef __PARKS_H__
#define __PARKS_H__

#include "time.h"
#include "cars.h"

/** PricesType is a float. */
typedef float PricesType;

/**
 * @brief Structure representing the prices of a parking lot.
 * 
 * This structure holds information about the cost of the 
 * first 4 15MIN periods, the cost of the next 15 MIN periods, 
 * and the cost of one day (max cost per day).
 */
typedef struct prices {
    PricesType x;
    PricesType y;
    PricesType z;
} Prices;

/**
 * @brief Structure representing a billing.
 * 
 * This structure holds information about the license plate of the car, the time
 * spent in the parking lot, the amount to bill the car, and a 
 * pointer to the next billing.
 */
typedef struct billing {
    char license[LICENSESIZE];
    Hours hours;
    PricesType value;
    struct billing *next;
} *Billing;

/**
 * @brief Structure representing all billing of a parking lot in a day.
 * 
 * This structure holds information about the date of the billing, the total
 * billing of the day, and a list of all the billing of the day.
 */
typedef struct dailyBilling {
    Date date;
    PricesType value;
    Billing billList;
    struct dailyBilling *next;
} *DailyBilling;


/**
 * @brief Structure representing a parking lot.
 * 
 * This structure holds information about a parking lot, including its name, 
 * capacity, number of free spots, prices, and daily billing.
 */
typedef struct park {
    char* name;
    int capacity;
    int freeSpots;
    Prices prices;
    DailyBilling billing;
} *Park;

/**
 * @brief Checks if the given capacity is invalid.
 * 
 * @param capacidade The capacity to check.
 * @return 1 if the capacity is invalid, 0 otherwise.
 */
short invalidCapacity(int capacidade);

/**
 * @brief Checks if the given cost is invalid.
 * 
 * @param x The cost of the first 4 15MIN periods.
 * @param y The cost of the next 15 MIN periods.
 * @param z The cost of one day (max cost per day).
 * @return 1 if the cost is invalid, 0 otherwise.
 */
short invalidCost(PricesType x, PricesType y, PricesType z);

/**
 * @brief Checks if the given park is invalid.
 * 
 * @param park The park to check.
 * @return 1 if the park is invalid, 0 otherwise.
 */
short equalPark(Park park1, Park park2);

/**
 * @brief Checks if the given park is full.
 * 
 * @param park The park to check.
 * @return 1 if the park is full, 0 otherwise.
 */
short isParkFull(Park park);

/**
 * @brief Creates a new parking lot.
 * 
 * @param name The name of the parking lot.
 * @param capacity The capacity of the parking lot.
 * @param x The cost of the first 4 15MIN periods.
 * @param y The cost of the next 15 MIN periods.
 * @param z The cost of one day (max cost per day).
 * @return The newly created parking lot.
 */
Park createPark(char *name, int capacity, 
                PricesType x, PricesType y, PricesType z);

/**
 * @brief Creates a new price structure.
 * 
 * @param x The cost of the first 4 15MIN periods.
 * @param y The cost of the next 15 MIN periods.
 * @param z The cost of one day (max cost per day).
 * @return The newly created price structure.
 */
Prices createPrices(PricesType x, PricesType y, PricesType z);

/**
 * @brief reduces the number of free spots in the parking lot by one.
 */
void oneLessFreeSpot(Park park);

/**
 * @brief increases the number of free spots in the parking lot by one.
 */
void oneMoreFreeSpot(Park park);

/**
 * @brief Calculates the billing of a car.
 * 
 * @param prices The prices of the parking lot.
 * @param entryTime The time of entry of the car.
 * @param exitTime The time of exit of the car.
 * @return The billing of the car.
 */
PricesType calculateBilling(Prices prices, Time entryTime, Time exitTime);

/**
 * @brief Adds a car to the billing list of the parking lot.
 * 
 * @param park The parking lot to add the car to.
 * @param license The license plate of the car.
 * @param time The time of the exit of the car.
 * @param billed The amount to bill the car.
 */
void addToParkBilling(Park park, char license[LICENSESIZE], 
                    Time time, PricesType billed);

/**
 * @brief Creates a new billing.
 * 
 * @param license The license plate of the car.
 * @param hours The time spent in the parking lot.
 * @param billed The amount to bill the car.
 * @return The newly created billing.
 */
Billing newBilling(char license[LICENSESIZE], Hours hours, PricesType billed);

/**
 * @brief Creates a new daily billing.
 * 
 * @param firstBill The first bill of the day.
 * @param date The date of the daily billing.
 * @return The newly created daily billing.
 */
DailyBilling newDailyBilling(Billing firstBill, Date date);

/**
 * @brief Gets the daily billing of a parking lot.
 * 
 * @param park The parking lot to get the daily billing from.
 * @param date The date of the daily billing.
 * @return The daily billing of the parking lot.
 */
DailyBilling getDailyBilling(Park park, Date date);

/**
 * @brief Prints the billing of a parking lot.
 * 
 * @param park The parking lot to print the billing of.
 */
void printBilling(Park park);

/**
 * @brief Prints the daily billing of a parking lot.
 * 
 * @param park The parking lot to print the daily billing of.
 * @param date The date of the daily billing.
 */
void printDailyBilling(Park park, Date date);

/**
 * @brief Frees a parking lot.
 * 
 * @param park The parking lot to free.
 */
void freePark(Park thisPark);

#endif
