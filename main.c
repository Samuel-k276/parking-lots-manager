#include <stdio.h>
#include <stdlib.h>


#include "main.h"

int main() {
    ListNode headNode = NULL;
    HashMap carMap = createCarHashMap();
    Time time = time0();

    char c = getchar();
    char *name;
    while (c != 'q') {
        switch(c) {
            case 'p':
                if (getchar() == '\0')
                    commandP0(headNode);
                else {
                    inputToCommandP1(headNode);
                }
                break;
            case 'e':

            case 's':

            case 'v':

            case 'f':

            case 'r':

            default:
                break;
        }

        c = getchar();
    }

    freeAll(headNode, carMap);
    return 0;
}

void freeAll(ListNode headNode, HashMap carMap) {
    freeCarHashMap(carMap);
    freeList(headNode);
}

void inputToCommandP1(ListNode headNode) {
    char *name = readName();
    int capacity;
    PricesType x, y, z;
    scanf("%d %f %f %f", &capacity, &x, &y, &z);
    commandP1(headNode, name, capacity, x, y, z);
    free(name);
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

    name[i] = '\0';
    return name;
}
