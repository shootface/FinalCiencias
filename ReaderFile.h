#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "Arboltemplate.h"
#include "estructuraUsuarios.h"
#include "estructuraAerolinea.h"

#ifndef reader
#define reader

using namespace std;

template <class T>
class readerFile{    
public:
    arbinor<T> tree;
    vector<string> lecturaFinal;
    readerFile(){}
    void readFile(string name); 
    arbinor<T> getArbol(){return tree;};
    vector<string> getLectura(){return lecturaFinal;};
    void organizarUsuarios(vector<string> lec);
    void organizarAerolineas(vector<string> lec);
private:
    void splitUser(string user1);
    void splitAero(string aero);
    void crearUsuario(vector<string> users);
    void crearAerolinea(vector<string> airlines);
};

//Encargado de leer el archivo y guardar cada linea leida en un vector
template <class T>
void readerFile<T>::readFile(string name){
    //Defino un string donde voy a guardar cada linea leida 
    string lectura;
    //Defino un elemento de tipo fsstream que se encarga de crear el buffer para la
    //lectura del archivo 
    fstream fs;
    //Abrir el archivo mediante el nombre que paso por parametro
    fs.open(name.c_str());
    //mientras exista una linea que leer va a hacer lo que esta dentro de la estructura iterativa
    while (! fs.eof() ) {
        //obtiene una linea de lectura que va ser guardada en la variable "lectura"
        getline (fs, lectura);
        //agrega esa linea leida al vector principal 
        lecturaFinal.push_back(lectura);
    }
    //cierra el archivo
    fs.close();
}
//LOS SIGUIENTES METODOS SON UNICOS PARA RECORRER LOS USUARIOS 


//Recorre el vector y envia cada linea leida que esta
//almacenado en el vector y lo envia al metodo split con
//el fin de organizar lo que esta dentro de esa linea
template <class T>
void readerFile<T>::organizarUsuarios(vector<string> lec){
    for(int i=0;i<100;i++){
        splitUser(lec[i]);
    }
}

template <class T>
void readerFile<T>::splitUser(string user1){
    string temp;
    vector<string> usertemp;
    vector<string> usertemp2;
    int found;
    cout << "Llegada : "<< user1 << endl;
    while(found!=-1){
        found = user1.find("/");
        temp = user1.substr(0, found); 
        usertemp.push_back(temp);
        user1 = user1.substr(found+1, user1.size());
    }
    found = NULL;
    crearUsuario(usertemp);
    usertemp.erase(usertemp.begin(), usertemp.end());	
}

template <class T>
void readerFile<T>::crearUsuario(vector<string> users){
    user *u = new user;
    u -> name = users[0];
    u -> lastname = users[1];
    u -> id = atoi(users[2].c_str());
    u -> sex = users[3][0];
    u -> age = atoi(users[4].c_str());
	tree.insertar(u);
}

//LOS SIGUIENTES METODOS SON UNICOS PARA RECORRER LAS AEROLINEAS


//Recorre el vector y envia cada linea leida que esta
//almacenado en el vector y lo envia al metodo split con
//el fin de organizar lo que esta dentro de esa linea
template <class T>
void readerFile<T>::organizarAerolineas(vector<string> lec){
    for(int i=0;i<50;i++){
        splitAero(lec[i]);
    }
}

template <class T>
void readerFile<T>::splitAero(string aero){
    string temp;
    vector<string> aerotemp;
    vector<string> aerotemp2;
    int found;
    cout << "Llegada : "<< aero << endl;
    while(found!=-1){
        found = aero.find("/");
        temp = aero.substr(0, found); 
        aerotemp.push_back(temp);
        aero = aero.substr(found+1, aero.size());
    }
    found = NULL;
    crearAerolinea(aerotemp);
    aerotemp.erase(aerotemp.begin(), aerotemp.end());
}

template <class T>
void readerFile<T>::crearAerolinea(vector<string> airlines){
    airline *a = new airline;
    a -> id = atoi(airlines[0].c_str());
    a -> name = airlines[1];
    a -> bankacc = airlines[2];
	tree.insertar(a);
}

#endif
