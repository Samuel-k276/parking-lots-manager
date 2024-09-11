#include <stdio.h>
#include "parks.h"
#include "cars.h"
#include "data.h"
#include "data.c"


int main() {
    Park AllParks;
    Car AllCars;

    DataEHora ultimoRegisto = inicializaPrimeiroRegisto();
    
    char input;
    while (input = getchar()) {

        switch(input) {
            case 'q':
                break;
            case 'p':
                comandoP(AllParks);
            case 'e':
                comandoE(AllParks, AllCars, &ultimoRegisto);


        }
        


    }

    cleanMemory();


    return 0;
}
