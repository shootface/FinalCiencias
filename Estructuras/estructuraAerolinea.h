#include "../Librerias/arbolTemplate.h"
#include "../Librerias/listaTemplate.h"

#include "estructuraVueloEspecifico.h"
#include "estructuraVueloPlaneado.h"
#include "estructuraAvion.h"

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
  lista<avion> aviones;
  void imprimirItinerarios();
  void imprimirAviones();
};

void airline::imprimirAviones() {
  avion aux;
  if (!aviones.lista_vacia()) {
    for (int i = 0; i < aviones.tamano_lista(); i++) {
      aux = aviones.obtenerDato(i);
      cout << "Avion: " << i << endl;
      if (aux.disponibilidad == true) {
        cout << "Disponibilidad: Disponible" << endl;
      } else {
        cout << "Disponibilidad: No disponible" << endl;
      }
      cout << "Nombre: " << aux.nombre << endl;
      cout << "Fabricante: " << aux.fabricante << endl;
      cout << "Capcidad: " << aux.capacidad << endl;
      cout << "Tipo: " << aux.tipo << endl;
      cout << endl;
    }
  }
}

void airline::imprimirItinerarios() {
  vueloEspecifico aux;
  if (!itinerario.lista_vacia()) {
    for (int i = 0; i < itinerario.tamano_lista(); i++) {
      aux = itinerario.obtenerDato(i);
      cout << "Itinerario: " << i << endl;
      cout << "ID: " << aux.id << endl;
      cout << "ID vuelo planeado: " << aux.idVueloPlaneado << endl;
      cout << "Sillas disponibles: " << aux.numeroSillasDisponibles << endl;
      cout << "Fecha: " << aux.fecha << endl;
      cout << "Precio Adulto: " << aux.precioAdulto << endl;
      cout << "Precio Niño: " << aux.precioNino << endl;
      cout << endl;
    }
  }
}

#endif
