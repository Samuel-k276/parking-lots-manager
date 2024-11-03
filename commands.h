/**
 * @file commands.h
 * @brief This file contains the definitions and function declarations for
 * managing commands, including processing, printing, and various utility
 * functions.
 * 
 * This file is part of the parking lots manager application, which is a simple
 * application for managing parking lots and cars parked in them.
 */
#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "hashmap.h"
#include "linkedList.h"

/**
 * @brief Processes the P0 command.
 * 
 * @param headNode The head of the list of parking lots.
 */
void commandP0 (ListNode headNode);

/**
 * @brief Processes the P1 command.
 * 
 * @param headNode The head of the list of parking lots.
 * @param name The name of the parking lot.
 * @param capacity The capacity of the parking lot.
 * @param x The cost of the first 4 15MIN periods.
 * @param y The cost of the next 15 MIN periods.
 * @param z The cost of one day (max cost per day).
 */
void commandP1 (ListNode *headNode, char* name, int capacity, 
                PricesType x, PricesType y, PricesType z);

/**
 * @brief Processes the E command.
 * 
 * @param headNode The head of the list of parking lots.
 * @param carMap The hash map of cars.
 * @param time The current time.
 * @param parkName The name of the parking lot.
 * @param license The license plate of the car.
 * @param newTime The entry time of the car.
 */
void commandE (ListNode *headNode, HashMap *carMap, Time *time, 
               char *parkName, char license[LICENSESIZE], Time newTime);

/**
 * @brief Processes the S command.
 * 
 * @param headNode The head of the list of parking lots.
 * @param carMap The hash map of cars.
 * @param time The current time.
 * @param parkName The name of the parking lot.
 * @param license The license plate of the car.
 * @param newTime The exit time of the car.
 */
void commandS (ListNode *headNode, HashMap *carMap, Time *time, 
               char *parkName, char license[LICENSESIZE], Time newTime);

/**
 * @brief Processes the V command.
 * 
 * @param carMap The hash map of cars.
 * @param license The license plate of the car.
 */
void commandV (HashMap carMap, char license[LICENSESIZE]);

/**
 * @brief Processes the F0 command.
 * 
 * @param headNode The head of the list of parking lots.
 * @param name The name of the parking lot.
 */
void commandF0 (ListNode headNode, char *name);

/**
 * @brief Processes the F1 command.
 * 
 * @param headNode The head of the list of parking lots.
 * @param name The name of the parking lot.
 * @param date The date to check.
 * @param currentDate The current date.
 */
void commandF1 (ListNode headNode, char *name, Date date, Date currentDate);

/**
 * @brief Processes the R command.
 * 
 * @param headNode The head of the list of parking lots.
 * @param name The name of the parking lot.
 * @param carMap The hash map of cars.
 */
void commandR (ListNode *headNode, char *name, HashMap *carMap);

/**
 * @brief Prints all park names in alphabetic order.
 * 
 * @param headNode The head of the list of parking lots.
 */
void printListSorted (ListNode headNode);

#endif