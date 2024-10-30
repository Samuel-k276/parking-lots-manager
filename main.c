#include <stdio.h>
#include "parks.h"
#include "cars.h"

#include "time.h"
#include "time.c"
#include "hashmap.h"
#include "hashmap.c"
#include "linkedList.h"
#include "linkedList.c"
#include "commands.h"
#include "commands.c"

int main() {
    ListNode headNode = NULL;
    HashMap carMap = createHashMap();
    Time time = time0();

    readInput(headNode, carMap, &time);

    freeAll(headNode, carMap);
    return 0;
}

void freeAll(ListNode headNode, HashMap carMap) {
    freeHashMap(carMap);
    freeList(headNode);
}

void readInput(ListNode headNode, HashMap carMap, Time *time) {
    char *command = (char*) malloc(2*sizeof(char));
    char c;
    int i = 0;
    while ((c = getchar()) != 'q') {
        while (c != '\n') {
            command[i++] = c;
            c = getchar();
        }
        command[++i] = '\0';
        inputToCommand(headNode, carMap, &time, command);
    }
}

void inputToCommand(ListNode headNode, HashMap carMap, Time *time, char *command) {
    switch(command[0]) {
        case 'p':
            if (command[1] == '\0')
                commandP0(headNode);
            else {
                
            }
        case 'e':

        case 's':

        case 'v':

        case 'f':

        case 'r':

        default:
            break;
    }
}
