#include <iostream>
#include "ReaderFile.h"
#include "Arboltemplate.h"
#include "estructuraUsuarios.h"
#include "estructuraAerolinea.h"
#include "gestionDatos.h"

using namespace std;

int main(){
	/*
    readerFile<user> rd;
    string name = "usuarios.txt";
    rd.readFile(name); 
    rd.organizarUsuarios(rd.getLectura());
    arbinor<user> arbolUser = rd.getArbol();
    cout<<endl;
    arbolUser.inorden(arbolUser.reRaiz());
    user *usfound = arbolUser.buscar(30102948);
    cout<<endl;
    cout << "Name : " << usfound -> name  << " ID : "<< usfound -> id <<endl;
    
    cout<<"/////////////////\\\\\\\\\\\\\\\\\///////////////"<<endl;
	cout<<endl;
	
    readerFile<airline> rda;
	name = "aerolineas.txt";
    rda.readFile(name); 
    rda.organizarAerolineas(rda.getLectura());
    arbinor<airline> arbolAero = rda.getArbol();
    cout<<endl;
    arbolAero.inorden(arbolAero.reRaiz());
    airline *airfound = arbolAero.buscar(5662);
    cout<<endl;
    cout << "Name : " << airfound->name  << " ID : "<< airfound->id << endl;
    */
    
    gestionDatos ges;
    ges.cargarUsuarios();
	ges.cargarAerolinea();
    return 0;
}

