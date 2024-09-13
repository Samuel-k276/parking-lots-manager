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
        const short maxDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        return (date.data.mes > 12 || date.data.mes < 1 || date.data.dia < 1 || date.data.dia > maxDays[date.data.mes - 1] || 
            date.hora.minutos > 59 || date.hora.minutos < 0 || date.hora.horas > 23 || date.hora.horas < 0);       
}

//return 1 if data 1 is the most recent
short mostRecent (DataEHora d0, DataEHora d1) {
    return (d1.data.ano > d0.data.ano ||
            (d1.data.ano == d0.data.ano && d1.data.mes > d0.data.mes) ||
            (d1.data.ano == d0.data.ano && d1.data.mes == d0.data.mes && d1.data.dia > d0.data.dia) ||
            (d1.data.ano == d0.data.ano && d1.data.mes == d0.data.mes && d1.data.dia == d0.data.dia 
             && d1.hora.horas > d0.hora.horas) ||
            (d1.data.ano == d0.data.ano && d1.data.mes == d0.data.mes && d1.data.dia == d0.data.dia 
             && d1.hora.horas == d0.hora.horas && d1.hora.minutos > d0.hora.minutos));
}

void changeDate (DataEHora *dateToChange, DataEHora newDate) {
    dateToChange->data.ano = newDate.data.ano;
    dateToChange->data.mes = newDate.data.mes;
    dateToChange->data.dia = newDate.data.dia;
    dateToChange->hora.horas = newDate.hora.horas;
    dateToChange->hora.minutos = newDate.hora.minutos;
}

int timeDiference (DataEHora recent, DataEHora old) {
    //calcular diferenca de meses em dias
    short dias;
    if (old.data.mes > recent.data.mes) {dias = -1*difDias(old, recent);}
    else {dias = difDias(recent, old);}

    while (recent.data.mes != old.data.mes) {
        recent.data.mes -= 1;
    }
    return ((recent.hora.minutos - old.hora.minutos) + (recent.hora.horas - old.hora.horas)*60 +
            ((recent.data.ano - old.data.ano)*365 + dias)*24*60);
}

short difDias (DataEHora recent, DataEHora old) {
    const short maxDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    short difDias;
    while (recent.data.mes != old.data.mes) {
        recent.data.mes -= 1;
        difDias += maxDays[recent.data.mes];
    }
    return difDias;
}