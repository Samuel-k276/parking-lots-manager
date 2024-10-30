#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "parks.h"
#include "cars.h"
#include "time.h"
#include "hashmap.h"
#include "linkedList.h"

void commandP0 (ListNode headNode);
void commandP1 (ListNode headNode, char* name, int capacity, PricesType x, PricesType y, PricesType z);
void comandoE (ListNode headNode, HashMap carMap, Time *time, char *parkName, char license[LICENSESIZE], Time newTime);


#endif