#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parks.h"

#define MAXPARKS 20



struct precos {
    TipoPrecos x;
    TipoPrecos y;
    TipoPrecos z;
};

typedef struct park {
    char* nome;
    int capacidade;
    int lugareslivres;
    
    struct precos precos;
    TipoPrecos faturacao;

    Park next;

};

int invalidCapacity (int capacidade) {
    return (capacidade <= 0);
}

int invalidCost (Precos preco) {
    return (preco.x <= 0 || preco.y <= 0 || preco.z <= 0 || preco.x >= preco.y || preco.y >= preco.z);
}

int parkingAlreadyExists (char* nome, Park beginOfList) {

    while (beginOfList != NULL) {
        if (strcmp(nome, beginOfList->nome) == 0) {
            return 1;
        }
    }


    return 0;
}

int tooManyParks (Park beginOfList) {
    Park current = beginOfList;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return (count >= MAXPARKS);
}


Park createPark (const char* name, int capacity, TipoPrecos x, TipoPrecos y, TipoPrecos z) {
    Park thisPark = (Park)malloc(sizeof(struct park));

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

void addPark (Park park, Park beginOfList) {

    if (beginOfList == NULL) {
        beginOfList = park;
        return;
    }

    Park current = beginOfList;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = park;
}
 
 
void commandP () {

}