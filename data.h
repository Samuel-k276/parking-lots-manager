#ifndef __DATA_H__
#define __DATA_H__

typedef struct hora Hora;
typedef struct data Data;
typedef struct dataehora DataEHora;

//constructors
DataEHora inicializaPrimeiroRegisto ();

//comparador
short invalidDate(DataEHora date);

#endif