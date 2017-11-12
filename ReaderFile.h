#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Librerias/arbolTemplate.h"
#include "Librerias/colaTemplate.h"

#include "Estructuras/estructuraAerolinea.h"
#include "Estructuras/estructuraAvion.h"
#include "Estructuras/estructuraUsuarios.h"
#include "Estructuras/estructuraVueloEspecifico.h"
#include "Estructuras/estructuraVueloPlaneado.h"

#ifndef READERFILE_H
#define READERFILE_H

using namespace std;

template <class T> class readerFile {
public:
	arbinor<T> tree;
	lista<T> iti;
	lista<T> avi;
	vector<string> lecturaFinal;
	readerFile() {}
	int readFile(string name);
	arbinor<T> getArbol();
	lista<T> getLista(int op);
	vector<string> getLectura() { return lecturaFinal; };
	void usuarios();
	void aerolineas();
	void trayectos();
	void itinerarios();
	void aviones();
	void organizarUsuarios(vector<string> lec);
	void organizarAerolineas(vector<string> lec);
	void organizarPlanTrayectos(vector<string> lec);
	void organizarItinerarios(vector<string> lec);
	void organizarAviones(vector<string> lec);
	vector<string> split(string dato);
	user *crearUsuario(vector<string> users);
	airline *crearAerolinea(vector<string> airlines);
	vueloPlaneado *crearPlanTrayectos(vector<string> pt);
	vueloEspecifico crearItinerario(vector<string> pt);
	avion crearAvion(vector<string> pt);

private:
};

template <class T> arbinor<T> readerFile<T>::getArbol() { return tree; }

template <typename T> lista<T> readerFile<T>::getLista(int op) {
	if (op == 1) {
    	return iti;
	} else if (op == 2) {
    	return avi;
  	}
  	return iti;
}

// Encargado de leer el archivo y guardar cada linea leida en un vector
template <class T> int readerFile<T>::readFile(string name) {
	// Defino un string donde voy a guardar cada linea leida
  	string lectura;
  	/* 
	  	Defino un elemento de tipo fstream que se encarga de crear el buffer para
	  	la  lectura del archivo
  	*/ 
  	fstream fs;

  	/* 
	  	mientras exista una linea que leer va a hacer lo que esta dentro de la
  		estructura iterativa
  	*/	
  	if (ifstream(name.c_str())) {
    // Abrir el archivo mediante el nombre que paso por parametro
    	fs.open(name.c_str(), ios::in);
    	do {
      		/* 
		  		obtiene una linea de lectura que va ser guardada en la variable
      			"lectura"
      		*/	
      		getline(fs, lectura);
      		// agrega esa linea leida al vector principal
      		lecturaFinal.push_back(lectura);
    	} while (!fs.eof());
    	// cierra el archivo
    	fs.close();
    	return 1;
  	} else {
    	return 0;
  	}
}

template <class T> vector<string> readerFile<T>::split(string dato) {
  	string temp;
  	vector<string> datotemp;
  	int found;
  	while (found != -1) {
    	found = dato.find("/");
    	temp = dato.substr(0, found);
    	datotemp.push_back(temp);
    	dato = dato.substr(found + 1, dato.size());
  	}
  	found = NULL;
  	return datotemp;
}

// LOS SIGUIENTES METODOS SON UNICOS PARA RECORRER LOS USUARIOS

/*
 	Recorre el vector y envia cada linea leida que esta
	almacenado en el vector y lo envia al metodo split con
	el fin de organizar lo que esta dentro de esa linea
*/	
template <class T> void readerFile<T>::usuarios() {
  	organizarUsuarios(getLectura());
}

template <class T> void readerFile<T>::organizarUsuarios(vector<string> lec) {
  	for (int i = 0; i < lec.size() - 1; i++) {
    	tree.insertar(crearUsuario(split(lec[i])));
  	}
}

template <class T> user *readerFile<T>::crearUsuario(vector<string> users) {
  	user *u = new user;
  	u->name = users[0];
  	u->lastname = users[1];
  	u->id = atoi(users[2].c_str());
  	u->sex = users[3][0];
  	u->age = atoi(users[4].c_str());
  	return u;
}

// LOS SIGUIENTES METODOS SON UNICOS PARA RECORRER LAS AEROLINEAS

/*
	Recorre el vector y envia cada linea leida que esta
	almacenado en el vector y lo envia al metodo split con
	el fin de organizar lo que esta dentro de esa linea
*/	
template <class T> void readerFile<T>::aerolineas() {
  	organizarAerolineas(getLectura());
}

template <class T> void readerFile<T>::organizarAerolineas(vector<string> lec) {
  	for (int i = 0; i < lec.size() - 1; i++) {
    	tree.insertar(crearAerolinea(split(lec[i])));
  	}
}

template <class T>
airline *readerFile<T>::crearAerolinea(vector<string> airlines) {
  	airline *a = new airline;
  	a->id = atoi(airlines[0].c_str());
  	a->name = airlines[1];
  	a->bankacc = airlines[2];
  	return a;
}

// LOS SIGUIENTES METODOS SON UNICOS PARA RECORRER PLAN DE TRAYECTOS

/*
	Recorre el vector y envia cada linea leida que esta
	almacenado en el vector y lo envia al metodo split con
	el fin de organizar lo que esta dentro de esa linea
*/
template <class T> void readerFile<T>::trayectos() {
  	organizarPlanTrayectos(getLectura());
}

template <class T>
void readerFile<T>::organizarPlanTrayectos(vector<string> lec) {
  	for (int i = 0; i < lec.size() - 1; i++) {
    	tree.insertar(crearPlanTrayectos(split(lec[i])));
 	}
}

template <class T>
vueloPlaneado *readerFile<T>::crearPlanTrayectos(vector<string> pt) {
  	vueloPlaneado *t = new vueloPlaneado;
  	cout << endl;
  	t->id = atoi(pt[0].c_str());
  	t->origin = pt[1];
  	t->posting = pt[2];
  	t->dayWeek = atoi(pt[3].c_str());
  	t->hi = atoi(pt[4].c_str());
  	t->hf = atoi(pt[5].c_str());
  	t->numS = atoi(pt[6].c_str());
  	t->nextT = atoi(pt[7].c_str());
  	return t;
}

// LOS SIGUIENTES METODOS SON UNICOS PARA RECORRER ITINERARIOS

/*
	Recorre el vector y envia cada linea leida que esta
	almacenado en el vector y lo envia al metodo split con
	el fin de organizar lo que esta dentro de esa linea
*/
template <class T> void readerFile<T>::itinerarios() {
  	organizarItinerarios(getLectura());
}

template <class T>
void readerFile<T>::organizarItinerarios(vector<string> lec) {
  	for (int i = 0; i < lec.size() - 1; i++) {
    	iti.insertar_final(crearItinerario(split(lec[i])));
  	}
}

template <class T>
vueloEspecifico readerFile<T>::crearItinerario(vector<string> pt) {
  	vueloEspecifico t;
  	t.id = atoi(pt[0].c_str());
  	t.idVueloPlaneado = atoi(pt[1].c_str());
  	t.numeroSillasDisponibles = atoi(pt[2].c_str());
  	t.fecha = pt[3];
  	t.precioAdulto = atof(pt[4].c_str());
  	t.precioNino = atof(pt[5].c_str());
  	return t;
}

// LOS SIGUIENTES METODOS SON UNICOS PARA RECORRER AVIONES

/*
	Recorre el vector y envia cada linea leida que esta
	almacenado en el vector y lo envia al metodo split con
	el fin de organizar lo que esta dentro de esa linea
*/
template <class T> void readerFile<T>::aviones() {
  	organizarAviones(getLectura());
}

template <class T> void readerFile<T>::organizarAviones(vector<string> lec) {
  	for (int i = 0; i < lec.size() - 1; i++) {
    avi.insertar_final(crearAvion(split(lec[i])));
  	}
}

template <class T> avion readerFile<T>::crearAvion(vector<string> pt) {
  	avion t;
  	t.disponibilidad = atoi(pt[0].c_str());
  	t.nombre = pt[1];
  	t.fabricante = pt[2];
  	t.capacidad = atoi(pt[3].c_str());
  	int tipo = atoi(pt[4].c_str());
  	if (tipo == 1) {
    	t.tipo = "Intercontinental";
  	} else if (tipo == 2) {
    	t.tipo = "Regional";
  	} else {
    	t.tipo = "No definido";
  	}
  	return t;
}

#endif
