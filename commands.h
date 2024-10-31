#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "hashmap.h"
#include "hashmap.c"
#include "linkedList.h"
#include "linkedList.c"

void commandP0 (ListNode headNode);
void commandP1 (ListNode *headNode, char* name, int capacity, PricesType x, PricesType y, PricesType z);
void commandE (ListNode *headNode, HashMap *carMap, Time *time, char *parkName, char license[LICENSESIZE], Time newTime);


#endif