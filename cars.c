#include <stdio.h>
#include "parks.h"
#include "cars.h"


#define LICENSESIZE 8

struct carro {
    char matricula[LICENSESIZE];
    TipoPrecos faturacao;    
    

    Carro next;    
};