#include "../Librerias/listaTemplate.h"

#include "estructuraVueloPlaneado.h"

#ifndef ESTRUCTURAVUELOESPECIFICO_H
#define ESTRUCTURAVUELOESPECIFICO_H

struct vueloEspecifico {
  	int id;
    int idVueloPlaneado;
  	vueloPlaneado vuelo;
  	int numeroSillasDisponibles = 0;
  	string fecha;
  	lista<silla> sillasVendidas;
  	lista<silla> sillasDisponibles;
  	double precioAdulto;
  	double precioNino;
    void asignarSillas();
    void venderSilla(string silla);
    void imprimirSillasDisponibles();
    void imprimirSillasVendidas();
};

void vueloEspecifico::asignarSillas() {
  silla aux;
  for (int i = 0; i < vuelo.avionVuelo.sillas.tamano_lista(); i++) {
    aux = vuelo.avionVuelo.sillas.obtenerDato(i);
    if (aux.disponible == true) {
      sillasDisponibles.insertar_final(aux);
      numeroSillasDisponibles++;
    } else {
      sillasVendidas.insertar_final(aux);
    }
  }
}

void vueloEspecifico::venderSilla(string id) {
  silla aux;
  for (int i = 0; i < sillasDisponibles.tamano_lista(); i++) {
    aux = sillasDisponibles.obtenerDato(i);
    if (aux.id == id) {
      sillasVendidas.insertar_final(aux);
      sillasDisponibles.eliminar(i);
      numeroSillasDisponibles--;
      break;
    }
  }
}

void vueloEspecifico::imprimirSillasDisponibles() {
  silla aux;
  if (!sillasDisponibles.lista_vacia()) {
    cout << "Disponibles" << endl;
    for (int i = 0; i < sillasDisponibles.tamano_lista(); i++) {
      aux = sillasDisponibles.obtenerDato(i);
      cout << aux.id << endl;
    }
    cout << endl;
  }
}

void vueloEspecifico::imprimirSillasVendidas() {
  silla aux;
  if (!sillasVendidas.lista_vacia()) {
    cout << "Vendidas" << endl;
    for (int i = 0; i < sillasVendidas.tamano_lista(); i++) {
      aux = sillasVendidas.obtenerDato(i);
      cout << aux.id << endl;
    }
    cout << endl;
  }
}

#endif
