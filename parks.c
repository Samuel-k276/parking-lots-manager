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

struct park {
    char* nome;
    int capacidade;
    int lugareslivres;
    
    struct precos precos;
    TipoPrecos faturacao;

    Park next;

};

short invalidCapacity (int capacidade) {
    return (capacidade <= 0);
}

short invalidCost (TipoPrecos x, TipoPrecos y, TipoPrecos z) {
    return (x <= 0 || y <= 0 || z <= 0 || x >= y || y >= z);
}

short parkingAlreadyExists (const char* name, Park beginOfList) {

    while (beginOfList != NULL) {
        if (strcmp(name, beginOfList->nome) == 0) {
            return 1;
        }
    }


    return 0;
}

short tooManyParks (Park beginOfList) {
    Park current = beginOfList;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return (count >= MAXPARKS);
}

char *lernome() {
    char *name = (char*)malloc(sizeof(char));
    char c = getchar();
    int i = 0;

    if (c == '"') {
        c = getchar();
        while (c != '"'){
            name[i++] = c;
            name = (char*)realloc(name, (i + 1)*sizeof(char));
            c = getchar();
        }
    
    } else {
        while (c != ' '){
            name[i++] = c;
            name = (char*)realloc(name, (i + 1)*sizeof(char));
            c = getchar();
        }
    }
    name[i] = '\0';

    return name;
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
 
 
void commandP (Park beginOfList) {
    if (getchar() == '\n') { 
        listAllParks(beginOfList); 
        return;
    }
    
    int capacity;
    TipoPrecos x, y, z;
    const char *name = lernome();
    scanf("%d %lf %lf %lf", &capacity, &x, &y, &z);

    if (invalidCapacity (capacity)) {
        printf("%d: invalid capacity.\n", capacity);
        return;
    }

    if (invalidCost (x, y, z)) {
        printf("invalid cost.\n");
        return;
    }

    if (parkingAlreadyExists (name, beginOfList)) {
        printf("%s: parking already exists.\n", name);
        return;
    }
        
    if (tooManyParks (beginOfList)) {
        printf("too many parks.\n");
        return;
    }

    Park newPark = createPark(name, capacity, x, y, z);
    free(name);
    addPark(newPark, beginOfList);
}

short noSuchPark (Park beginOfList, const char* nameToFind) {
    Park current = beginOfList;
    while (strcmp(current->nome, nameToFind)) {
        current = current->next;
    }
    return (current == NULL);
}

Park findPark (Park beginOfList, const char* nameToFind) {
    Park current = beginOfList;
    while (strcmp(current->nome, nameToFind)) {
        current = current->next;
    }
    return current;
}

void oneLessFreeSpot (Park beginOfList, const char* parkName) {
    Park thisPark = findPark(beginOfList, parkName);
    thisPark->lugareslivres -= 1;
}

void freePark(Park thisPark) {
    free(thisPark->nome);
    //freehistorico
    while(thisPark->capacidade) {

    }
    free(thisPark);
}

void deletePark(const char* name, Park beginOfList) {

}