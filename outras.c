#include <stdio.h>
#include "structures.h"

inicializaUltimoResgisto () {
  DataEHora Registo;
  Registo.data.dia = 1;
  Registo.data.mes = 1;
  Registo.data.ano = 1800;
  Registo.hora.horas = 0;
  Registo.hora.minutos = 0;

  return Registo*;
}
