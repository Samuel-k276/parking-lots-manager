#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

#define MAXPARKS 20

int invalidCapacity (int capacidade) {
    return (capacidade <= 0);
}

int invalidCost (Precos preco) {
    return (preco.x <= 0 || preco.y <= 0 || preco.z <= 0 || preco.x >= preco.y || preco.y >= preco.z);
}

int parkingAlreadyExists (char* nome, Parque* beginOfList) {

    while (beginOfList != NULL) {
        if (strcmp(nome, beginOfList->nome) == 0) {
            return 1;
        }
    }


    return 0;
}

int tooManyParks (Parque* beginOfList) {
    Parque* current = beginOfList;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return (count >= MAXPARKS);
}

