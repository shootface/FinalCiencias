#include <iostream>

#include "../Librerias/listaTemplate.h"

#include "estructuraSilla.h"

#ifndef ESTRUCTURAAVIONES_H
#define ESTRUCTURAAVIONES_H

using namespace std;

struct avion {
<<<<<<< HEAD
	bool disponibilidad;
	string nombre;
	string fabricante;
	int capacidad;
	string tipo;
=======
  bool disponibilidad;
  string nombre;
  string fabricante;
  int capacidad;
  string tipo;
  lista<silla> sillas;
  void imprimirSillas();
>>>>>>> 0758aff653eebdf0e496d735b5fb19b134560611
};

void avion::imprimirSillas() {
  silla aux;
  if (!sillas.lista_vacia()) {
    for (int i = 0; i < sillas.tamano_lista(); i++) {
      aux = sillas.obtenerDato(i);
      cout << aux.id << endl;
    }
  }
}

#endif
