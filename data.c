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

short invalidDate(DataEHora date) {
        const int maxDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        return (date.data.mes > 12 || date.data.mes < 1 || date.data.dia < 1 || date.data.dia > maxDays[date.data.mes - 1] || 
            date.hora.minutos > 59 || date.hora.minutos < 0 || date.hora.horas > 23 || date.hora.horas < 0);       
}