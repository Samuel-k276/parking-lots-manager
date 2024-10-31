#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include "parks.h"
#include "parks.c"

typedef struct listNode *ListNode;

#define MAXPARKS 20

ListNode createListNode(Park park);
void appendListNode(ListNode node, ListNode *beginOfList);
ListNode findListNode(char *name, ListNode *headNode);
short nodeExists(char *name, ListNode headNode);
short tooManyParks(ListNode headNode);
void removeListNode(char *name, ListNode *headNode);
void printAllNodes(ListNode headNode);
void freeList(ListNode headNode);

#endif