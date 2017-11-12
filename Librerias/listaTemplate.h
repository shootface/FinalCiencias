#include <cstdlib>
#include <iostream>

#include "../Estructuras/estructuraNodo.h"

#ifndef LISTATEMPLATE_H
#define LISTATEMPLATE_H

using namespace std;

template <class T>
class lista {

  nodo<T> *cab;
  int tam;

public:
  lista() {
    cab = NULL;
    tam = 0;
  }
  void imprimir();
  bool lista_vacia();
  int tamano_lista();
  T obtenerDato(int pos);
  bool eliminar(int pos);
  void insertar_final(T infoNueva);
  void insertar_pos(T infoNueva, int pos);
  void insertar_inicio(T infoNueva);
};

template <class T>
void lista<T>::insertar_pos(T infoNueva, int pos) {

  if (pos > tam) {
    insertar_final(infoNueva);
  } else {
    if (pos == 1) {
      insertar_inicio(infoNueva);
    } else {
      nodo<T> *nuevo, *aux;
      nuevo = new nodo<T>;

      nuevo->dato = infoNueva;
      aux = cab;

      int p = 1;
      while ((p < pos - 1) && (aux != NULL)) {
        aux = aux->sig;
        p++;
      }

      nuevo->sig = aux->sig;
      aux->sig = nuevo;
    }
    tam++;
  }
}

template <class T>
void lista<T>::insertar_final(T infoNueva) {

  nodo<T> *nuevo;
  nuevo = new nodo<T>;

  nuevo->dato = infoNueva;
  nuevo->sig = NULL;

  if (tam == 0) {
    cab = nuevo;
  } else {
    nodo<T> *aux;
    aux = cab;

    while (aux->sig != NULL) {
      aux = aux->sig;
    }
    aux->sig = nuevo;
  }
  tam++;
}

template <class T>
void lista<T>::insertar_inicio(T infoNueva) {

  nodo<T> *nuevo;
  nuevo = new nodo<T>;

  nuevo->dato = infoNueva;
  nuevo->sig = cab;
  cab = nuevo;

  tam++;
}

template <class T>
T lista<T>::obtenerDato(int pos) {

  nodo<T> *aux;
  aux = cab;

  int p = 1;
  while ((p < pos) && (aux != NULL)) {
    aux = aux->sig;
    p++;
  }

  if (aux != NULL) {
    return aux->dato;
  }

  return aux->dato;
}

template <class T>
bool lista<T>::eliminar(int pos) {

  if (tam >= pos) {
    nodo<T> *temp;
    temp = cab;

    if (pos == 1) {
      cab = temp->sig;
      delete temp;
    } else {
      for (int i = 1; i < pos - 1; i++) {
        temp = temp->sig;
      }

      nodo<T> *aux;
      aux = temp->sig;
      temp->sig = aux->sig;

      delete aux;
    }
    tam--;
    return true;
  } else {
    return false;
  }
}

template <class T>
bool lista<T>::lista_vacia() {

  if (tam == 0) {
    return true;
  } else {
    return false;
  }
}

template <class T>
int lista<T>::tamano_lista() {

  return tam;
}

template <class T>
void lista<T>::imprimir() {

  if (lista_vacia()) {
    cout << "La lista no tiene Informacion" << endl;
  } else {
    cout << "La informacion de la lista es:" << endl;

    nodo<T> *aux;
    aux = cab;

    int pos = 1;
    while (aux != NULL) {
      cout << "  " << endl;
      cout << "Info " << pos << ": " << aux->dato.idVueloPlaneado << endl;
      cout << "Info " << pos << ": " << aux->dato.numeroSillasDisponibles << endl;
      cout << "Info " << pos << ": " << aux->dato.fecha << endl;
      cout << "Info " << pos << ": " << aux->dato.precioAdulto << endl;
      cout << "Info " << pos << ": " << aux->dato.precioNino << endl;
      aux = aux->sig;
      pos++;
    }
  }
}

#endif
