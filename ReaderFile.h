#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include "Arboltemplate.h"
#include "estructuraUsuarios.h"
#include "estructuraAerolinea.h"
#include "estructuraVueloPlaneado.h"
#include "estructuraVueloEspecifico.h"
#include "colaTemplate.h"

#ifndef reader
#define reader

using namespace std;

template <class T>
class readerFile{
	public:
    	arbinor<T> tree;
		lista<T> iti;
        vector<string> lecturaFinal;
    	readerFile(){}
    	int readFile(string name);
	    arbinor<T> getArbol();
		lista<T> getLista();
        vector<string> getLectura(){return lecturaFinal;};
        void usuarios();
        void aerolineas();
        void trayectos();
        void itinerarios();
	    void organizarUsuarios(vector<string> lec);
	    void organizarAerolineas(vector<string> lec);
	    void organizarPlanTrayectos(vector<string> lec);
        void organizarItinerarios(vector<string> lec);
        vector<string> split(string dato);
        user *crearUsuario(vector<string> users);
	    airline *crearAerolinea(vector<string> airlines);
        vuelopla *crearPlanTrayectos(vector<string> pt);
		vueloes crearItinerario(vector<string> pt);
	private:
	    
};
template <class T>
arbinor<T> readerFile<T>::getArbol(){
    return tree;
}

template <typename T>
lista<T> readerFile<T>::getLista(){
	return iti;
}
//Encargado de leer el archivo y guardar cada linea leida en un vector
template <class T>
int readerFile<T>::readFile(string name){
    //Defino un string donde voy a guardar cada linea leida
    string lectura;
    //Defino un elemento de tipo fstream que se encarga de crear el buffer para la
    //lectura del archivo
    fstream fs;

    //mientras exista una linea que leer va a hacer lo que esta dentro de la estructura iterativa
    if(ifstream(name.c_str())){
        //Abrir el archivo mediante el nombre que paso por parametro
        fs.open(name.c_str());
        while (! fs.eof() ) {
            //obtiene una linea de lectura que va ser guardada en la variable "lectura"
            getline (fs, lectura);
            //agrega esa linea leida al vector principal
            lecturaFinal.push_back(lectura);
        }
        //cierra el archivo
        fs.close();
        return 1;
    }else{
        return 0;
    }

}
template <class T>
vector<string> readerFile<T>::split(string dato){
    string temp;
    vector<string> datotemp;
    int found;
    while(found!=-1){
        found = dato.find("/");
        temp = dato.substr(0, found);
        datotemp.push_back(temp);
        dato = dato.substr(found+1, dato.size());
    }
    found = NULL;
    return datotemp;
}
//LOS SIGUIENTES METODOS SON UNICOS PARA RECORRER LOS USUARIOS


//Recorre el vector y envia cada linea leida que esta
//almacenado en el vector y lo envia al metodo split con
//el fin de organizar lo que esta dentro de esa linea
template <class T>
void readerFile<T>::usuarios(){
    organizarUsuarios(getLectura());
}
template <class T>
void readerFile<T>::organizarUsuarios(vector<string> lec){
    for(int i=0;i<lec.size()-1;i++){
        tree.insertar(crearUsuario(split(lec[i])));
    }
}
template <class T>
user *readerFile<T>::crearUsuario(vector<string> users){
    user *u = new user;
    u -> name = users[0];
    u -> lastname = users[1];
    u -> id = atoi(users[2].c_str());
    u -> sex = users[3][0];
    u -> age = atoi(users[4].c_str());
    return u;
}

//LOS SIGUIENTES METODOS SON UNICOS PARA RECORRER LAS AEROLINEAS


//Recorre el vector y envia cada linea leida que esta
//almacenado en el vector y lo envia al metodo split con
//el fin de organizar lo que esta dentro de esa linea
template <class T>
void readerFile<T>::aerolineas(){
    organizarAerolineas(getLectura());
}
template <class T>
void readerFile<T>::organizarAerolineas(vector<string> lec){
    for(int i=0;i<lec.size()-1;i++){
        tree.insertar(crearAerolinea(split(lec[i])));
    }
}
template <class T>
airline *readerFile<T>::crearAerolinea(vector<string> airlines){
    airline *a = new airline;
    a -> id = atoi(airlines[0].c_str());
    a -> name = airlines[1];
    a -> bankacc = airlines[2];
    return a;
}

//LOS SIGUIENTES METODOS SON UNICOS PARA RECORRER PLAN DE TRAYECTOS


//Recorre el vector y envia cada linea leida que esta
//almacenado en el vector y lo envia al metodo split con
//el fin de organizar lo que esta dentro de esa linea
template <class T>
void readerFile<T>::trayectos(){
    organizarPlanTrayectos(getLectura());
}
template <class T>
void readerFile<T>::organizarPlanTrayectos(vector<string> lec){
    for(int i=0;i<lec.size()-1;i++){
        tree.insertar(crearPlanTrayectos(split(lec[i])));
    }
}
template <class T>
vuelopla *readerFile<T>::crearPlanTrayectos(vector<string> pt){
    vuelopla *t = new vuelopla;
    t -> id = atoi(pt[0].c_str());
    t -> origin = pt[1];
    t -> posting = pt[2];
    t -> dayWeek = atoi(pt[3].c_str());
    t -> hi = atoi(pt[4].c_str());
    t -> hf = atoi(pt[5].c_str());
    t -> numS = atoi(pt[6].c_str());
    t -> nextT = atoi(pt[7].c_str());
    return t;
}

// LOS SIGUIENTES METODOS SON UNICOS PARA RECORRER ITINERARIOS

// Recorre el vector y envia cada linea leida que esta
// almacenado en el vector y lo envia al metodo split con
// el fin de organizar lo que esta dentro de esa linea
template <class T>
void readerFile<T>::itinerarios(){
    organizarItinerarios(getLectura());
}
template <class T>
void readerFile<T>::organizarItinerarios(vector<string> lec) {
  for (int i = 0; i < lec.size() - 1; i++) {
    iti.insertar_final(crearItinerario(split(lec[i])));
  }
}

template <class T> 
vueloes readerFile<T>::crearItinerario(vector<string> pt) {
  vueloes t;
  t.numSillasDisponibles = atoi(pt[0].c_str());
  t.fecha = pt[1];
  t.precio = atof(pt[2].c_str());
  return t;
}

#endif
