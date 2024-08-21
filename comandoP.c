#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "errors.c"
#include "outras.c"

Parque* createPark (char* name, int capacity, TipoPrecos x, TipoPrecos y, TipoPrecos z) {
    Parque* thisPark = (Parque*)malloc(sizeof(Parque));

    strcpy(thisPark->nome, name);
    thisPark->capacidade = capacity;
    thisPark->lugareslivres = capacity;
    thisPark->precos.x = x;
    thisPark->precos.y = y;
    thisPark->precos.z = z;
    thisPark->faturacao = 0;
    thisPark->next = NULL;

    return thisPark;
}

void addPark (Parque* Park, Parque* beginOfList) {

    if (beginOfList == NULL) {
        beginOfList = Park;
        return;
    }

    Parque* current = beginOfList;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = Park;
}
 
 
void commandP () {

}