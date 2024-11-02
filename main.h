#ifndef __MAIN_H__
#define __MAIN_H__

#include "commands.h"

#define ENTRY 1
#define EXIT 0

char* readName();
void freeAll(ListNode *headNode, HashMap *carMap);

void inputToCommandP1(ListNode *headNode);
void inputToCommandEntryOrExit(ListNode *headNode, HashMap *carMap, Time *time, short type);
void inputToCommandV(HashMap carMap);
void inputToCommandF(ListNode headNode, Date currentDate);
void inputToCommandR(ListNode *headNode, HashMap *carMap);

#endif