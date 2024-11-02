#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

ListNode createListNode(Park park) {
    ListNode thisNode = (ListNode)malloc(sizeof(struct listNode));
    thisNode->prev = NULL;
    thisNode->park = park;
    thisNode->next = NULL;

    return thisNode;
}

ListNode findListNode(char *name, ListNode *headNode) {
    ListNode current = *headNode;
    while (current != NULL) {
        if (current->park != NULL && current->park->name != NULL && 
            strcmp(current->park->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
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
    node->prev = current;
    current->next = node;
}

void removeListNode(char *name, ListNode *head) {
    ListNode node = findListNode(name, head);
    
    if (*head == node) {
        *head = node->next;
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    freePark(node->park);
    free(node);
}

short nodeExists(char *name, ListNode headNode) {
    return findListNode(name, &headNode) != NULL;
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

void printAllNodes(ListNode headNode) {
    ListNode current = headNode;
    while (current != NULL) {
        printf("%s %d %d\n", current->park->name, 
        current->park->capacity, current->park->freeSpots);
        
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
