#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

#define MAXPARKS 20

struct listNode {
    ListNode prev;
    Park park;
    ListNode next;
};

ListNode createListNode(Park park) {
    ListNode thisNode = (ListNode)malloc(sizeof(struct listNode));
    thisNode->prev = NULL;
    thisNode->park = park;
    thisNode->next = NULL;

    return thisNode;
}

void appendListNode(ListNode node, ListNode *beginOfList) {
    if (*beginOfList == NULL) {
        *beginOfList = node;
        return;
    }
    ListNode current = *beginOfList;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
}

ListNode findListNode(char *name, ListNode headNode) {
    ListNode current = headNode;
    while (current != NULL && strcmp(current->park->name, name)) {
        current = current->next;
    }
    return current;
}

short nodeExists(char *name, ListNode headNode) {
    return findListNode(name, headNode) != NULL;
}

short tooManyParks(ListNode headNode) {
    ListNode current = headNode;
    int i = 0;
    while (current != NULL) {
        current = current->next;
        i++;
    }
    if (i < MAXPARKS) i = 0;
    return i;
}

void removeListNode(char *name, ListNode headNode) {
    ListNode node = findListNode(name, headNode);
    if (node->prev == NULL) {
        headNode = node->next;
        return;
    }

    node->prev->next = node->next;
    freePark(node->park);
    free(node);
}

void printAllNodes(ListNode headNode) {
    ListNode current = headNode;
    while (current != NULL) {
        printf("%s %d %d\n", current->park->name, current->park->capacity, current->park->freeSpots);
        current = current->next;
    }
}

void freeList(ListNode headNode) {
    if (headNode == NULL)
        return;

    ListNode current = headNode;
    ListNode nextNode;        

    while (current != NULL) {
        nextNode = current->next;  
        freePark(current->park);    
        free(current);              
        current = nextNode;         
    }
}
