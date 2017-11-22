#include <iostream>
#include "ReaderFile.h"
#include "Librerias/arbolTemplate.h"
#include "Estructuras/estructuraUsuarios.h"
#include "Estructuras/estructuraAerolinea.h"
#include "Estructuras/estructuraAvion.h"
#include "gestionDatos.h"
#include "WriterFile.h"

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
    writerFile wf;
    ges.cargarUsuarios();
    ges.cargarAerolinea();
    cout << "Ahora vamos a realizar una busque de los itinerarios" << endl;
    ges.buscarItinerarios(); 
    //arbinor<airline> *aero = ges.getArbinorAirline();
    //arbinor<vueloPlaneado> t= aero->buscar(5662)->trayectos;
    //t.inorden(t.reRaiz());
    //cout << "Action :" << ges.agregarTrayectorias("11/Bogota/Madrid/2/1600/600/50/0",5662)<< endl;
    //cout << "agregar" << endl;
    //t.inorden(t.reRaiz());
    /*
    airline *prueba = aero->buscar(5662);
    prueba->imprimirAviones();
    prueba->imprimirItinerarios();
    //prueba->imprimirTrayectos();
    */
    /*
    for (int i = 0; i < prueba->aviones.tamano_lista(); i++) {
      cout << "Avion: " << i << endl;
      prueba->aviones.obtenerDato(i).imprimirSillas();
      cout << endl;
    }

    string temp = "999/New_York/Madrid/2/1600/600/50/0";
    cout << "Estado de la operación : " << ges.agregarTrayectorias(temp,5662) << endl;
    t.inorden(t.reRaiz());
    //wf.write("Avianca_T.txt","876/New_York/Madrid/2/1600/600/50/0");
    */
    return 0;
}
