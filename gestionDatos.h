#include "ReaderFile.h"
#include "Arboltemplate.h"
#include "estructuraUsuarios.h"
#include "estructuraAerolinea.h"
#include "colaTemplate.h"

#ifndef gestion
#define gestion

class gestionDatos{
    arbinor<user> usuarios;
    arbinor<airline> aerolineas;
    arbinor<vuelopla> vp;
	public:
		int cargarAerolinea();
	    int cargarUsuarios();
		gestionDatos(){}
	private:
    	int cargarTrayectorias(arbinor<airline> arbolAir);
};
/*
	Llama la libreria encargada de la gestion de los datos de
	los archivos planos de los usuarios con el fin de almacenarlos
*/
int gestionDatos::cargarUsuarios(){
    readerFile<user> rdu;
    string name = "usuarios.txt";
    if(rdu.readFile(name)){
        rdu.organizarUsuarios(rdu.getLectura());
        arbinor<user> arbolUser = rdu.getArbol();
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
		arbinor<airline> arbolAir = rda.getArbol();
		arbolAir.inorden(arbolAir.reRaiz());
		cargarTrayectorias(arbolAir);
		return 1;
	} else {
		return 0;
	}
}

int gestionDatos::cargarTrayectorias(arbinor<airline> arbolAir){
	cola<string> *cs = arbolAir.inordenCola();
	while(!cs->ColaVacia()){
		string name = ""+cs->AtenderCola()+"_T.txt";
		cout<<name<<endl; // para verificacion 
		readerFile<vuelopla> rdvp;
		if(rdvp.readFile(name)){
			rdvp.organizarPlanTrayectos(rdvp.getLectura());
			arbinor<vuelopla> arbolTray = rdvp.getArbol();
			/*
				Aca se debe insertar en la estructura aerolinea
			*/
			cout<<"Paso"<<endl;
		} else {
			cout<<"Next"<<endl;
		}
	}
}

#endif
