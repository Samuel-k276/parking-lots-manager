#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "hashmap.h"
#include "linkedList.h"

void commandP0 (ListNode headNode);
void commandP1 (ListNode *headNode, char* name, int capacity, 
                PricesType x, PricesType y, PricesType z);
void commandE (ListNode *headNode, HashMap *carMap, Time *time, 
               char *parkName, char license[LICENSESIZE], Time newTime);
void commandS (ListNode *headNode, HashMap *carMap, Time *time, 
               char *parkName, char license[LICENSESIZE], Time newTime);
void commandV (HashMap carMap, char license[LICENSESIZE]);
void commandF0 (ListNode headNode, char *name);
void commandF1 (ListNode headNode, char *name, Date date, Date currentDate);
void commandR (ListNode *headNode, char *name, HashMap *carMap);
void printListSorted (ListNode headNode);

#endif