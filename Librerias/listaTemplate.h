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
<<<<<<< HEAD
  	lista() {
    	cab = NULL;
    	tam = 0;
  	}
  	void imprimirItinerarios();
  	void imprimirAviones();
  	bool lista_vacia();
  	int tamano_lista();
  	T obtenerDato(int pos);
  	bool eliminar(int pos);
  	void insertar_final(T infoNueva);
  	void insertar_pos(T infoNueva, int pos);
  	void insertar_inicio(T infoNueva);
=======
  lista() {
    cab = NULL;
    tam = 0;
  }
  void imprimirItinerarios();
  bool lista_vacia();
  int tamano_lista();
  T obtenerDato(int pos);
  bool eliminar(int pos);
  void insertar_final(T infoNueva);
  void insertar_pos(T infoNueva, int pos);
  void insertar_inicio(T infoNueva);
>>>>>>> 0758aff653eebdf0e496d735b5fb19b134560611
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
<<<<<<< HEAD
    	aux = cab;   
=======
    	aux = cab;
>>>>>>> 0758aff653eebdf0e496d735b5fb19b134560611
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
<<<<<<< HEAD
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
=======

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

  return aux->dato; // Aca esta el error
>>>>>>> 0758aff653eebdf0e496d735b5fb19b134560611
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
<<<<<<< HEAD
}

template <class T>
void lista<T>::imprimirItinerarios() {
	if (lista_vacia()) {
    	cout << "La lista no tiene Informacion" << endl;
  	} else {
    	cout << "La informacion de la lista es:" << endl;
		nodo<T> *aux;
    	aux = cab;
		int pos = 1;
    	while (aux != NULL) {
      		cout << "  " << endl;
      		cout << "Info " << pos << ": " << aux->dato.id << endl;
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

template <typename T>
void lista<T>::imprimirAviones() {
	if (lista_vacia()) {
    	cout << "La lista no tiene Informacion" << endl;
  	} else {
    	cout << "La informacion de la lista es:" << endl;
		nodo<T> *aux;
    	aux = cab;
		int pos = 1;
    	while (aux != NULL) {
			cout << "  " << endl;
			cout << "Info " << pos << ": " << aux->dato.disponibilidad << endl;
      		cout << "Info " << pos << ": " << aux->dato.nombre << endl;
      		cout << "Info " << pos << ": " << aux->dato.fabricante << endl;
      		cout << "Info " << pos << ": " << aux->dato.capacidad << endl;
      		cout << "Info " << pos << ": " << aux->dato.tipo << endl;
      		aux = aux->sig;
      		pos++;
    	}
  	}
}

=======
}
>>>>>>> 0758aff653eebdf0e496d735b5fb19b134560611
#endif
