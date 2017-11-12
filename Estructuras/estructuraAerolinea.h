#include "../Librerias/arbolTemplate.h"
#include "../Librerias/listaTemplate.h"

#include "estructuraVueloEspecifico.h"
#include "estructuraVueloPlaneado.h"

#ifndef ESTRUCTURAAEROLINE_H
#define ESTRUCTURAAEROLINE_H

// Estructura para agregar los datos de las aerolineas existentes en el archivo
// plano de texto
struct airline {
  int id;
  string name;
  string bankacc;
  airline *izq;
  airline *der;
  arbinor<vueloPlaneado> trayectos;
  lista<vueloEspecifico> itinerario;
};

#endif
