/**
 * @file main.h
 * @brief This file contains the definitions and function declarations for the
 * main functions of the parking lots manager application.
 * 
 * This file is part of the parking lots manager application, which is a simple
 * application for managing parking lots and cars parked in them.
 */
#ifndef __MAIN_H__
#define __MAIN_H__

#include "commands.h"

/** The code for E command */
#define ENTRY 1

/** The code for S command */
#define EXIT 0

/**
 * @brief Reads a name from the input.
 *
 * @return The name read from the input.
 */
char* readName();

void freeAll(ListNode *headNode, HashMap *carMap);

/**
 * @brief Processes a command.
 *
 * @param c The command type.
 * @param headNode The head of the list of parking lots.
 * @param carMap The hash map of cars.
 * @param time The current time.
 */
void processCommand(char c, ListNode *headNode, HashMap *carMap, Time *time);

/**
 * @brief Reads the input for the command P and processes it.
 *
 * @param headNode The head of the list of parking lots.
 */
void inputToCommandP(ListNode *headNode);

/**
 * @brief Reads the input for the commands E/S and processes it.
 *
 * @param headNode The head of the list of parking lots.
 * @param carMap The hash map of cars.
 * @param time The current time.
 */
void inputToCommandEntryOrExit(ListNode *headNode, HashMap *carMap, 
                               Time *time, short type);


/**
 * @brief Reads the input for the command V and processes it.
 * 
 * @param carMap The hash map of cars.
 */
void inputToCommandV(HashMap carMap);

/**
 * @brief Reads the input for the command F and processes it.
 *
 * @param headNode The head of the list of parking lots.
 * @param carMap The hash map of cars.
 * @param time The current time.
 */
void inputToCommandF(ListNode headNode, Date currentDate);

/**
 * @brief Reads the input for the command R and processes it.
 *
 * @param headNode The head of the list of parking lots.
 * @param carMap The hash map of cars.
 */
void inputToCommandR(ListNode *headNode, HashMap *carMap);

#endif