#include "listaTemplate.h"
#ifndef estructuraVueloEspecifico
#define estructuraVueloEspecifico

struct vueloes {
  int numSillasDisponibles; // Numero de sillas disponibles
  string fecha;
  lista<string> sillasVendidas; // String o char?
  lista<string> sillasDisponibles;
  double precio;
};

#endif
