#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parks.h"
#include "parks.c"
#include "cars.h"
#include "cars.c"
#include "time.h"
#include "time.c"
#include "hashmap.h"
#include "hashmap.c"
#include "linkedList.h"
#include "linkedList.c"

void commandP (Park beginOfList, char* name, int capacity, PricesType x, PricesType y, PricesType z) {
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

void comandoE(ListNode AllParks, HashMap AllCars, Time *time, char *parkName, char license[LICENSESIZE], Time newTime) {
    if (noSuchPark(AllParks, parkName)) {

        return;
    }

    Car thisCar;
    if (carExists(AllCars, license)) {
        thisCar = findCar(AllCars, license);
    } else {
        thisCar = createCar(license);
    }

    if (isParked(thisCar)) {

        return;
    }
    
    carEntry(parkName, thisCar, time);
    oneLessFreeSpot(thisCar);
    changeDate(time, newTime);
}