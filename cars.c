#include <stdio.h>
#include "parks.h"
#include "cars.h"
#include "data.h"

#define LICENSESIZE 6

struct carro {
    char matricula[LICENSESIZE];
    TipoPrecos faturacao;    
    

    Car next;    
};


void comandoE(Park AllParks, Car AllCars, DataEHora *ultimoRegisto) {

}