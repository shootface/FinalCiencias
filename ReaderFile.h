#include <iostream>
#include <fstream>
#include <vector>
#include "Arboltemplate.h"
#include "estructuraUsuarios.h"

#ifndef reader
#define reader

using namespace std;
template <class T>
class readerFile{    
public:
    arbinor<T> arbolUser;
    vector<string> lecturaFinal;
    readerFile(){}
    void readFile(string name); 
    arbinor<T> getArbol(){return arbolUser;};
    vector<string> getLectura(){return lecturaFinal;};
    void organizarUsuarios(vector<string> lec);
private:
    void splitUser(string user1);
    void crearUsuario(vector<string> users);
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
    fs.open(name);
    //mientras exista una linea que leer va a hacer lo que esta dentro de la estructura iterativa
    while (! fs.eof() ) {
        //obtiene una linea de lectura que va ser guardada en la variable "lectura"
        getline (fs,lectura);
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
        temp = user1.substr(0,found); 
        usertemp.push_back(temp);
        user1 = user1.substr(found+1,user1.size());
    }
    found = NULL;
    crearUsuario(usertemp);
    usertemp.erase(usertemp.begin(),usertemp.end());
}
template <class T>
void readerFile<T>::crearUsuario(vector<string> users){
    user *u = new user;
    u -> name = users[0];
    u -> lastname = users[1];
    u -> id = stoi (users[2],nullptr,0);
    u -> sex = users[3][0];
    arbolUser.insertar(u);
}
#endif