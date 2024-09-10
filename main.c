#include <stdio.h>
#include "parks.h"
#include "cars.h"
#include "data.h"
#include "data.c"


int main() {
    Park AllParks;
    Carro AllCars;

    DataEHora ultimoRegisto = inicializaPrimeiroRegisto();
    
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
