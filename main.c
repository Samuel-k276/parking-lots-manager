#include <stdio.h>
#include <stdlib.h>


#include "main.h"

int main() {
    ListNode headNode = NULL;
    HashMap carMap = createCarHashMap();
    Time time = time0();

    char c = getchar();
    while (c != 'q') {
        switch(c) {
            case 'p':
                if (getchar() == '\n')
                    commandP0(headNode);
                else {
                    inputToCommandP1(&headNode);
                }
                break;
            case 'e':
                inputToCommandEntryOrExit(&headNode, &carMap, &time, ENTRY);
                break;
            case 's':
                inputToCommandEntryOrExit(&headNode, &carMap, &time, EXIT);
                break;
            case 'v':
                inputToCommandV(carMap);
                break;
            case 'f':
                break;
            case 'r':
                break;
            default:
                break;
        }

        c = getchar();
    }

    freeAll(headNode, carMap);
    return 0;
}

void freeAll(ListNode headNode, HashMap carMap) {
    if (carMap != NULL) freeCarHashMap(carMap);
    if (headNode != NULL) freeList(headNode);
}

void inputToCommandP1(ListNode *headNode) {
    char *name = readName();
    int capacity;
    PricesType x, y, z;
    scanf("%d %f %f %f", &capacity, &x, &y, &z);
    commandP1(headNode, name, capacity, x, y, z);
}

void inputToCommandEntryOrExit(ListNode *headNode, HashMap *carMap, Time *time, short type) {
    getchar();
    char *name = readName();
    char license[LICENSESIZE];
    int day, month, year, hours, minutes;
    scanf("%c%c-%c%c-%c%c %d-%d-%d %d:%d", &license[0], &license[1], &license[2], &license[3],
                                    &license[4], &license[5], &day, &month, &year, &hours, &minutes);
    license[6] = '\0';
    Time new = newTime(day, month, year, hours, minutes);
    if (type == ENTRY) commandE(headNode, carMap, time, name, license, new);
    if (type == EXIT) commandS(headNode, carMap, time, name, license, new);
}

void inputToCommandV(HashMap carMap) {
    getchar();
    char license[LICENSESIZE];
    scanf("%c%c-%c%c-%c%c", &license[0], &license[1], &license[2], 
                            &license[3], &license[4], &license[5]);
    license[6] = '\0';
    commandV(carMap, license);
}

char* readName() {
    char c = getchar(); 
    char end = ' ';
    char *name = (char *)malloc(sizeof(char));;
    int i;
    if (c == '"') {
        end = c;
        c = getchar();
    }

    for (i = 0; c != end; i++) {
        name[i] = c;
        c = getchar();
        name = (char *)realloc(name, (i+2)* sizeof(char));
    }
    if (end == '"') getchar();
    name[i] = '\0';
    return name;
}
