#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "parks.h"
#include "cars.h"
#include "data.h"
#include "hashmap.h"

char* readName();
char* readCommand();

void commandP (Park beginOfList);
void comandoE(Park AllParks, HashMap carMap, DataEHora *ultimoRegisto);


#endif