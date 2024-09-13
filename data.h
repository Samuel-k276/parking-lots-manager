#ifndef __DATA_H__
#define __DATA_H__

typedef struct hora Hora;
typedef struct data Data;
typedef struct dataehora DataEHora;

//constructors
DataEHora inicializaPrimeiroRegisto ();
void changeDate (DataEHora *dateToChange, DataEHora newDate);

//comparador
short invalidDate (DataEHora date);
short mostRecent (DataEHora data1, DataEHora data2);

//getters
int timeDiference (DataEHora recent, DataEHora old);
short difDias (DataEHora recent, DataEHora old);

#endif