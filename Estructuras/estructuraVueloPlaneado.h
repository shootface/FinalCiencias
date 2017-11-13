#include <iostream>

#include "estructuraAvion.h"

#ifndef ESTRUCTURAVUELOPLANEADO_H
#define ESTRUCTURAVUELOPLANEADO_H

using namespace std;

struct vueloPlaneado {
  	// Codigo de vuelo
  	int id;
  	// Origen
  	string origin;
  	// Destino
  	string posting;
  	// dia de la semana
  	/*
      	Los datos validos seran:
          	0 : lunes
          	1 : martes
          	2 : miercoles
          	3 : jueves
          	4 : viernes
          	5 : sabado
          	6 : domingo
   	*/
  	int dayWeek;
  	// Hora de salida
  	int hi;
  	// Hora de llegado
  	int hf;
  	// Numero de sillas
  	int numS;
  	// Apuntadores del arbol
  	vueloPlaneado *der;
  	vueloPlaneado *izq;
  	// posible escala
  	int nextT;
    avion avionVuelo;
    void numeroDeSillas() {
      numS = avionVuelo.capacidad;
    }
};

#endif
