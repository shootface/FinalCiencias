#include "../Librerias/listaTemplate.h"

#ifndef ESTRUCTURAVUELOESPECIFICO_H
#define ESTRUCTURAVUELOESPECIFICO_H

struct vueloEspecifico {
  int idVueloPlaneado;
  int numeroSillasDisponibles;
  string fecha;
  lista<string> sillasVendidas;
  lista<string> sillasDisponibles;
  double precioAdulto;
  double precioNino;
};

#endif
