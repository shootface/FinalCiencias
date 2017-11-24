#include "ReaderFile.h"
#include "WriterFile.h"
#include "busquedasDatos.h"

#include "Librerias/arbolTemplate.h"
#include "Librerias/colaTemplate.h"

#include "Estructuras/estructuraAerolinea.h"
#include "Estructuras/estructuraAvion.h"
#include "Estructuras/estructuraRelleno.h"
#include "Estructuras/estructuraUsuarios.h"

#ifndef GESTIONDATOS_H
#define GESTIONDATOS_H

class gestionDatos {
  arbinor<user> *usuarios;
  arbinor<airline> *aerolineas;
  arbinor<user> us;
  arbinor<airline> aer;
  arbinor<vueloPlaneado> vp;
  lista<vueloEspecifico> ve;
  lista<avion> aviones;

public:
  gestionDatos() {}
  int cargarAerolinea();
  int cargarUsuarios();
  int agregarTrayectorias(string t, int idAero);
  arbinor<user> *getArbinorUser() { return usuarios; };
  arbinor<airline> *getArbinorAirline() { return aerolineas; };
  void login(int id);
  /*
	Meotdos encargados de la busqueda dentro de estas estructuras
	estos metodos con solo una llamada ya que se creo una clase encargada
	de realizar estas busquedas
  */
	void buscarItinerarios(int day);
private:
  int agregarTrayectoria(vueloPlaneado *vpnew, int idAero);
  void cargarTrayectorias(arbinor<airline> *arbolAir);
  void cargarItinerarios(arbinor<airline> *arbolAir);
  void cargarAviones(arbinor<airline> *arbolAir);
};
/*
        Llama la libreria encargada de la gestion de los datos de
        los archivos planos de los usuarios con el fin de almacenarlos
*/

/*--------------------------------------------------------------------*/

// METODOS PUBLICOS
// Cargar usuarios del archivo de texto plano
int gestionDatos::cargarUsuarios() {
  // llamar a la clase encargada de leer y organizar el archivo
  readerFile<user> rdu;
  // definir el nombre del archivo que se va a leer
  string name = "Archivos/usuarios.txt";
  // Se verifica si el archivo se puede leer en el IF
  if (rdu.readFile(name)) {
    rdu.usuarios();
    // Obtiene el arbol despues de crear los usuarios y agregarlos a un ARBINOR
    us = rdu.getArbol();
    // Se le asigna la direccion de memoria al apuntador
    usuarios = &us;
    // retorna 1 porque la operacion se realizo de manera satisfactoria
    return 1;
  } else {
    // retorna 0 porque la operacion no se pudo realizar
    return 0;
  }
}

/*
        Carga aerolineas del archivo de texto plano
        Ademas cargar los trayectos y los itinerarios de los
        archivos planos
*/
int gestionDatos::cargarAerolinea() {
  readerFile<airline> rda;
  string name = "Archivos/aerolineas.txt";
  if (rda.readFile(name)) {
    rda.aerolineas();
    aer = rda.getArbol();
    aerolineas = &aer;
    cargarAviones(aerolineas);
    cargarTrayectorias(aerolineas);
    cargarItinerarios(aerolineas);
    return 1;
  } else {
    return 0;
  }
}

int gestionDatos::agregarTrayectorias(string t, int idAero) {
  readerFile<vueloPlaneado> rd;
  airline *a = aer.buscar(idAero);
  arbinor<vueloPlaneado> vpF = a->trayectos;
  string name = "Archivos/" + a->name + "_T.txt";
  bool es = true;
  vueloPlaneado *vptemp = rd.crearPlanTrayectos(rd.split(t));
  cola<int> *id = vpF.inOrdenV();
  while (!id->ColaVacia()) {
    int temp = id->AtenderCola();
    cout << "DATO EN COLA : " << temp << endl;
    vueloPlaneado *vtemp = vpF.buscar(temp);
    if (vtemp->dayWeek == vptemp->dayWeek) {
      if (vtemp->origin == vptemp->origin &&
          vptemp->posting == vtemp->posting) {
        cout << "repetido" << endl;
        es = false;
      } else {
        cout << "no esta repetido en la" << endl;
      }
    }
  }
  if (es) {
    agregarTrayectoria(vptemp, idAero);
    writerFile wr;
    wr.write(name, t);
    cout << "no esta repetido";
    return 1;
  } else {
    return 0;
  }
}

/*--------------------------------------------------------------------*/
// METODOS PRIVADOS
void gestionDatos::cargarTrayectorias(arbinor<airline> *arbolAir) {
  cola<tRelleno> *cs = arbolAir->inordenCola();
  while (!cs->ColaVacia()) {
    tRelleno temp = cs->AtenderCola();
    string name = "Archivos/" + temp.name + "_T.txt";
    // cout<<name<<endl; // para verificacion
    readerFile<vueloPlaneado> rdvp;
    if (rdvp.readFile(name)) {
      // BASE
      rdvp.trayectos();
      vp = rdvp.getArbol();
      airline *tempair = arbolAir->buscar(temp.id);
      for (int i = 0; i < tempair->aviones.tamano_lista(); i++) {
        avion auxAvi = tempair->aviones.obtenerDato(i);
        vueloPlaneado *auxPla = vp.buscar(auxAvi.idVueloPlaneado);
        if (auxPla != NULL) {
          auxPla->avionVuelo = auxAvi;
          auxPla->numeroDeSillas();
        }
      }

      tempair->trayectos = vp;
      // FIN BASE
    }
  }
}
void gestionDatos::cargarItinerarios(arbinor<airline> *arbolAir) {
  cola<tRelleno> *cs = arbolAir->inordenCola();
  while (!cs->ColaVacia()) {
    tRelleno temp = cs->AtenderCola();
    string name = "Archivos/" + temp.name + "_I.txt";
    readerFile<vueloEspecifico> rdves;
    if (rdves.readFile(name)) {
      rdves.itinerarios();
      ve = rdves.getLista(1);
      airline *tempair = arbolAir->buscar(temp.id);
      tempair->itinerario = ve;
    }
  }
}
void gestionDatos::cargarAviones(arbinor<airline> *arbolAir) {
  cola<tRelleno> *cs = arbolAir->inordenCola();
  while (!cs->ColaVacia()) {
    tRelleno temp = cs->AtenderCola();
    string name = "Archivos/" + temp.name + "_V.txt";
    readerFile<avion> rdAvion;
    if (rdAvion.readFile(name)) {
      rdAvion.aviones();
      aviones = rdAvion.getLista(2);
      airline *tempair = arbolAir->buscar(temp.id);
      tempair->aviones = aviones;
    }
  }
}

// Agrega trayectorias nuevas al arbol de su respectiva aerolinea
int gestionDatos::agregarTrayectoria(vueloPlaneado *vpnew, int idAero) {
  if (vpnew != NULL && idAero != NULL) {
    airline *air = aer.buscar(idAero);
    cout << "Aerolinea a ingresar " << air->name << endl;
    if (air != NULL) {
      arbinor<vueloPlaneado> vp = air->trayectos;
      vp.insertar(vpnew);
      air->trayectos = vp;
      return 1;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}
/*METODOS DE BUSQUEDA*/
void gestionDatos::buscarItinerarios(int day){
	busDatos bs;
	bs.busIti(aer,day);
}

/*METODOS */

#endif
