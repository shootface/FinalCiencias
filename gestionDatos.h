#include "ReaderFile.h"
#include "Arboltemplate.h"
#include "estructuraUsuarios.h"
#include "estructuraAerolinea.h"
#include "colaTemplate.h"
#include "estructuraRelleno.h"

#ifndef gestion
#define gestion

class gestionDatos{
    arbinor<user> *usuarios;
	arbinor<airline> *aerolineas;
	arbinor<user> us;
    arbinor<airline> aer;
    arbinor<vuelopla> vp;
	public:
		gestionDatos(){}
		int cargarAerolinea();
	    int cargarUsuarios();
		arbinor<user> *getArbinorUser(){return usuarios;};
		arbinor<airline> *getArbinorAirline(){return aerolineas;};
	private:
		void cargarTrayectorias(arbinor<airline> *arbolAir);
		void cargarItinerarios(arbinor<airline> *arbolAir);
		arbinor<vuelopla> setEscala(arbinor<vuelopla> vp);
};
/*
	Llama la libreria encargada de la gestion de los datos de
	los archivos planos de los usuarios con el fin de almacenarlos
*/
int gestionDatos::cargarUsuarios(){
    readerFile<user> rdu;
	string name = "usuarios.txt";
	cout << "tengo la lectura" << endl;
    if(rdu.readFile(name)){
		cout << "se puede leer" << endl;
		rdu.organizarUsuarios(rdu.getLectura());
		us = rdu.getArbol();
        usuarios = &us;
        //arbolUser.inorden(arbolUser.reRaiz());
        return 1;
    }else{
        return 0;
    }
}
int gestionDatos::cargarAerolinea(){
	readerFile<airline> rda;
	string name = "aerolineas.txt";
	if(rda.readFile(name)){
		rda.organizarAerolineas(rda.getLectura());
		aer = rda.getArbol();
		aerolineas = &aer;
		cargarTrayectorias(aerolineas);
		return 1;
	} else {
		return 0;
	}
}
void gestionDatos::cargarTrayectorias(arbinor<airline> *arbolAir){
	cola<tRelleno> *cs = arbolAir->inordenCola();
	while(!cs->ColaVacia()){
		tRelleno temp = cs->AtenderCola();
		string name = ""+temp.name+"_T.txt";
		//cout<<name<<endl; // para verificacion 
		readerFile<vuelopla> rdvp;
		if(rdvp.readFile(name)){
			//BASE
			rdvp.organizarPlanTrayectos(rdvp.getLectura());
			vp = rdvp.getArbol();
			airline *tempair = arbolAir->buscar(temp.id);
			tempair -> trayectos = vp;
			//FIN BASE
			cout << tempair -> name << endl;
		}
	}
}
#endif
