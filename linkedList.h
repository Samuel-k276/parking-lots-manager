/**
 * @file linkedList.h
 * @brief This file contains the definitions and function declarations for 
 * managing linked lists, including creation, insertion, retrieval, and 
 * deletion of nodes.
 * 
 * This file is part of the parking lots manager application, which is a simple
 * application for managing parking lots and cars parked in them.
 */
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include "parks.h"

/** The maximum number of parks */
#define MAXPARKS 20

/**
 * @brief Structure representing a node in a linked list.
 *
 * This structure holds a pointer to the previous node, a park, 
 * and a pointer to the next node.
 */
typedef struct listNode {
    struct listNode *prev;
    Park park;
    struct listNode *next;
} *ListNode;

/**
 * @brief Creates a new node with the given park.
 *
 * @param park The park to create the node with.
 * @return The newly created node.
 */
ListNode createListNode(Park park);

/**
 * @brief Finds a node with the given name.
 *
 * @param name The name of the park to find.
 * @param headNode The head of the list to search.
 * @return The node with the given name.
 */
ListNode findListNode(char *name, ListNode *headNode);

/**
 * @brief Appends a node to the end of the list.
 *
 * @param node The node to append.
 * @param beginOfList The head of the list to append to.
 */
void appendListNode(ListNode node, ListNode *beginOfList);

/**
 * @brief Removes a node from the list.
 *
 * @param name The name of the park to remove.
 * @param headNode The head of the list to remove from.
 */
void removeListNode(char *name, ListNode *headNode);

/**
 * @brief Checks if a node with the given name exists.
 *
 * @param name The name of the park to check.
 * @param headNode The head of the list to check.
 * @return 1 if the node exists, 0 otherwise.
 */
short nodeExists(char *name, ListNode headNode);

/**
 * @brief Checks if there are too many parks.
 *
 * @param headNode The head of the list to check.
 * @return 1 if there are too many parks, 0 otherwise.
 */
short tooManyParks(ListNode headNode);

/**
 * @brief Prints all nodes in the list.
 *
 * @param headNode The head of the list to print.
 */
void printAllNodes(ListNode headNode);

/**
 * @brief Frees all nodes in the list.
 *
 * @param headNode The head of the list to free.
 */
void freeList(ListNode headNode);

#endif