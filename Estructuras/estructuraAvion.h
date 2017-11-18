#include <iostream>

#include "../Librerias/listaTemplate.h"

#include "estructuraSilla.h"

#ifndef ESTRUCTURAAVIONES_H
#define ESTRUCTURAAVIONES_H

using namespace std;

struct avion {
  int id;
  int idVueloPlaneado;
  bool disponibilidad;
  string nombre;
  string fabricante;
  int capacidad;
  string tipo;
  lista<silla> sillas;
};

#endif
