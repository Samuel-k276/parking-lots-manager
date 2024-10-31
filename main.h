#ifndef __MAIN_H__
#define __MAIN_H__

#include "commands.h"
#include "commands.c"

char* readName();
void freeAll(ListNode headNode, HashMap carMap);

void inputToCommandP1(ListNode *headNode);
void inputToCommandE(ListNode *headNode, HashMap *carMap, Time *time);

#endif