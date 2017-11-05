#include "ReaderFile.h"
#ifndef  gestion
#define gestion

class gestionDatos{
    arbinor<user> usuarios;
    arbinor<airline> aerolineas;
    arbinor<vuelopla> vp;
    gestionDatos(){
    }
public:
    int cargarAerolinea();
    int cargarUsuarios();
private:
    int cargarTrayectorias();
};
//Llama la libreria encargada de la gestion de los datos de
//los archivos planos de los usuarios con el fin de almacenarlos
int gestionDatos::cargarUsuarios(){
    readerFile<user> rd;
    string name = "usuarios.txt";
    if(rd.readFile(name)==1){
        rd.organizarUsuarios(rd.getLectura());
        arbinor<user> arbolUser = rd.getArbol();
        return 1;
    }else{
        return 0;
    }
}
int gestionDatos::cargarAerolinea(){}
int gestionDatos::cargarTrayectorias(){}
#endif