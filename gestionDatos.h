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
    lista<vueloes> ve;
	public:
		gestionDatos(){}
		int cargarAerolinea();
		int cargarUsuarios();
		int agregarTrayectorias(string t,int idAero);
		int agregarItinerarios(string t,int idAero);
		arbinor<user> *getArbinorUser(){return usuarios;};
		arbinor<airline> *getArbinorAirline(){return aerolineas;};
	private:
		int agregarTrayectoria(vuelopla *vpnew,int idAero);
		int agregarItinerarios(vueloes vsnew,int idAero);
		void cargarTrayectorias(arbinor<airline> *arbolAir);
		void cargarItinerarios(arbinor<airline> *arbolAir);
};
/*
	Llama la libreria encargada de la gestion de los datos de
	los archivos planos de los usuarios con el fin de almacenarlos
*/
/*--------------------------------------------------------------------*/
//METODOS PUBLICOS
//Cargar usuarios del archivo de texto plano
int gestionDatos::cargarUsuarios(){
	//llamar a la clase encargada de leer y organizar el archivo
	readerFile<user> rdu;
	//definir el nombre del archivo que se va a leer
	string name = "usuarios.txt";
	//Se verifica si el archivo se puede leer en el IF 
    if(rdu.readFile(name)){
		rdu.usuarios();
		//Obtiene el arbol despues de crear los usuarios y agregarlos a un ARBINOR
		us = rdu.getArbol();
		//Se le asigna la direccion de memoria al apuntador
		usuarios = &us;
		//retorna 1 porque la operacion se realizo de manera satisfactoria
        return 1;
    }else{
		//retorna 0 porque la operacion no se pudo realizar
        return 0;
    }
}
//Carga aerolineas del archivo de texto plano
//Ademas cargar los trayectos y los itinerarios de los
//archivos planos
int gestionDatos::cargarAerolinea(){
	readerFile<airline> rda;
	string name = "aerolineas.txt";
	if(rda.readFile(name)){
		rda.aerolineas();
		aer = rda.getArbol();
		aerolineas = &aer;
		cargarTrayectorias(aerolineas);
    	cargarItinerarios(aerolineas);
		return 1;
	} else {
		return 0;
	}
}
int gestionDatos::agregarTrayectorias(string t,int idAero){
	readerFile<vuelopla> rd;
	if(agregarTrayectoria(rd.crearPlanTrayectos(rd.split(t)),idAero)){
		return 1;
	}else{
		return 0;
	}
}

/*--------------------------------------------------------------------*/
//METODOS PRIVADOS
void gestionDatos::cargarTrayectorias(arbinor<airline> *arbolAir){
	cola<tRelleno> *cs = arbolAir->inordenCola();
	while(!cs->ColaVacia()){
		tRelleno temp = cs->AtenderCola();
		string name = ""+temp.name+"_T.txt";
		//cout<<name<<endl; // para verificacion
		readerFile<vuelopla> rdvp;
		if(rdvp.readFile(name)){
			//BASE
			rdvp.trayectos();
			vp = rdvp.getArbol();
			airline *tempair = arbolAir->buscar(temp.id);
			tempair -> trayectos = vp;
			//FIN BASE
		}
	}
}
void gestionDatos::cargarItinerarios(arbinor<airline> *arbolAir) {
  cola<tRelleno> *cs = arbolAir->inordenCola();
  while (!cs->ColaVacia()) {
    tRelleno temp = cs->AtenderCola();
    string name = "" + temp.name + "_I.txt";
    readerFile<vueloes> rdves;
    if (rdves.readFile(name)) {
      rdves.itinerarios();
      ve = rdves.getLista();
      airline *tempair = arbolAir->buscar(temp.id);
      tempair->itinerario = ve;
    }
  }
}
//Agrega trayectorias nuevas al arbol de su respectiva aerolinea
int gestionDatos::agregarTrayectoria(vuelopla *vpnew,int idAero){
	if(vpnew!=NULL && idAero!= NULL){
		airline *air = aer.buscar(idAero);
		cout << "Aerolinea a ingresar "<< air->name << endl;
		if(air!=NULL){
			arbinor<vuelopla> vp = air->trayectos;
			vp.insertar(vpnew);
			air -> trayectos = vp;
			return 1;
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}
//Agregar itinerarios nuevos al arbol de su respectiva aerolinea
int gestionDatos::agregarItinerarios(vueloes vsnew,int idAero){}
#endif
