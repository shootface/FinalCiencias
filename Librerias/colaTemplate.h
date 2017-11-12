#include <iostream>

#include "../Estructuras/estructuraNodo.h"

#ifndef COLATEMPLATE
#define COLATEMPLATE

using namespace std;

template <class T> class cola {
  nodo<T> *cab, *fin;

public:
  cola() { cab = fin = NULL; }

  void InsCola(T i);
  T AtenderCola();
  void ImprimirCola();
  bool ColaVacia();
  ~cola();
};

template <class T> void cola<T>::InsCola(T i) {
  nodo<T> *nuevo;
  nuevo = new nodo<T>;
  nuevo->dato = i;
  nuevo->sig = NULL;
  if (cab == NULL) {
    cab = nuevo;
  } else {
    fin->sig = nuevo;
  }
  fin = nuevo;
}

template <class T> T cola<T>::AtenderCola() {
  T x;
  nodo<T> *aux = cab;
  cab = aux->sig;
  x = aux->dato;
  delete aux;
  return x;
}

template <class T> void cola<T>::ImprimirCola() {
  nodo<T> *aux;
  aux = cab;
  while (aux != NULL) {
    cout << aux->dato << " ";
    aux = aux->sig;
  }
}

template <class T> bool cola<T>::ColaVacia() { return (cab == NULL); }

template <class T> cola<T>::~cola() {
  nodo<T> *aux;
  while (cab != NULL) {
    aux = cab;
    cab = aux->sig;
    delete aux;
  }
  delete cab;
}

#endif
