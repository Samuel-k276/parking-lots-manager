#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parks.h"
#include "parks.c"
#include "linkedList.h"

#define MAXPARKS 20

struct listNode {
    ListNode before;
    Park park;
    ListNode next;
};

ListNode createListNode(Park park) {
    ListNode thisNode = (ListNode)malloc(sizeof(struct listNode));
    thisNode->park = park;
    thisNode->next = NULL;

    return thisNode;
}

void appendListNode(ListNode node, ListNode beginOfList) {
    ListNode current = beginOfList;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
}

ListNode findListNode(char *name, ListNode beginOfList) {
    ListNode current = beginOfList;
    while (current != NULL && strcmp(current->park->name, name)) {
        current = current->next;
    }
    return current;
}

short nodeExists(char *name, ListNode beginOfList) {
    return findListNode(name, beginOfList) != NULL;
}

void removeListNode(char *name, ListNode beginOfList) {
    ListNode node = findListNode(name, beginOfList);
    if (node->before == NULL) {
        beginOfList = node->next;
        return;
    }

    node->before->next = node->next;
    freePark(node->park);
    free(node);
}

