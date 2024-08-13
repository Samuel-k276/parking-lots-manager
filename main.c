#include <stdio.h>
#include "structures.h"
#include "outras.c"

int main() {
    Parque AllParks;
    Carro AllCars;

    DataEHora ultimoRegisto;
    ultimoRegisto = inicializaPrimeiroRegisto();
    
    char input;
    while (input = getchar()) {

        switch(input) {
            case 'q':
                break;
            case 'p':
                comandoP();


        }
        


    }

    cleanMemory();


    return 0;
}
