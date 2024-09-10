#include <stdio.h>
#include "data.h"


struct hora {
    int horas;
    int minutos;
};

struct data {
    int dia;
    int mes;
    int ano;
};

struct dataehora {
    Data data;
    Hora hora;
};

DataEHora inicializaPrimeiroRegisto () {
  DataEHora Registo;
  Registo.data.dia = 1;
  Registo.data.mes = 1;
  Registo.data.ano = 1800;
  Registo.hora.horas = 0;
  Registo.hora.minutos = 0;
 
  return Registo;
}

