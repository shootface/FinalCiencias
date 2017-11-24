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
  void cargador();
  int agregarTrayectorias(string t, int idAero);
  arbinor<user> *getArbinorUser() { return usuarios; };
  arbinor<airline> *getArbinorAirline() { return aerolineas; };
  int login(int id);
  int generaListas();
  void accionar();
  /*
	Meotdos encargados de la busqueda dentro de estas estructuras
	estos metodos con solo una llamada ya que se creo una clase encargada
	de realizar estas busquedas
  */
	void buscarItinerarios(int day,user *us);
  void buscarOrigenDestino(string origen,string destino,user *us);
  void listarAero();
  void listarDest();
  void listarUsers();
  void listarMul();
  void listarVP();
  void listarVE();
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

//Metodo inicializador del programa
void gestionDatos::cargador(){
  if(cargarUsuarios() && cargarAerolinea()){
    accionar();
  }else{
    cout << "ERROR EN LA CARGA" << endl;
  }
}
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
void gestionDatos::buscarItinerarios(int day,user *us){
	busDatos bs;
	bs.busIti(aer,us,day);
}
void gestionDatos::buscarOrigenDestino(string origen,string destino,user *us){
  busDatos bs;
  bs.busOD(aer,us,origen,destino);
}

void gestionDatos::listarAero(){
	busDatos bs;
	bs.listAero(aer);
}

void gestionDatos::listarDest(){
	busDatos bs;
	bs.listDest(aer);
}

void gestionDatos::listarUsers(){
	busDatos bs;
	bs.listUsers(us);	
}

void gestionDatos::listarMul(){
	busDatos bs;
	bs.listMul(aer);
}

void gestionDatos::listarVP(){
	busDatos bs;
	bs.listVPS(aer);
}

void gestionDatos::listarVE(){
	busDatos bs;
	bs.listVES(aer);
}

/*METODOS DE ACCESO*/
int gestionDatos::login(int id){
  user *tempus = us.buscar(id);
  airline *temp = aer.buscar(id);
  if(tempus!=NULL){
    bool hecho=true;
    cout << "Hola, " << tempus->name <<endl;
    while(hecho){
      cout << "Selecione una opcion\n" << endl;
      cout << "1. Realizar una compra\n2. Ver historial de compras\n"<< endl;
      int opcion;
      cin >> opcion;
      if(opcion==1){
        cout << "Desea realizar un busqueda por: \n";
        cout << "1. Dia\n2. Origen-Destino\n";
        cin >> opcion;
        if(opcion==1){
          cout << "En que dia desea buscar los vuelos :" << endl;
          cout << "Los datos validos seran:\n0 : lunes\n1 : martes\n2 : miercoles\n3 : jueves\n4 : viernes\n5 : sabado\n6 : domingo\n" ;
          int day;
          cin >> day;
          buscarItinerarios(day,tempus);
          return 1;
        }else if(opcion==2){
          cout << "Ingrese la ciudad de origen" << endl;
          string origen;
          cin >> origen;
          cout << "Ingrese la ciudad de destino" << endl;
          string destino;
          cin >> destino;
          buscarOrigenDestino(origen,destino,tempus);
          return 1;
        }
      }else if(opcion==2){
        //Metodo que muestra el historial 
      }else{
        return 0;
      }
    }
  }else if(temp!=NULL){
     cout << "Hola, " << temp->name << endl;
     bool hecho=true;
     while(hecho){
       cout << "1. Registrar un nuevo vueloPlaneado\n2. Registrar un nuevo vueloEspecifico" << endl;
       int opcion;
       cin >> opcion;
       if(opcion==1){
         //Metodo que crea VP
         hecho = false;
       }else if(opcion==2){
         //Metodo que crea VE
         hecho = false;
       }else{
         cout << "Ingrese una opcion valida " << endl;
       } 
     }

  }else if(id==666){
    cout << "Reportes" << endl;
  }
}

int gestionDatos::generaListas(){
	int ctr = 1;
	while (ctr == 1){
		int opc;
		cout << " Elija que desea listar: " << endl;
  		cout << "1. Aerolineas\n2. Destinos por aerolinea\n3. Usuarios registrados\n4. Viajes multiples\n5. Vuelos Planeados\n6. Vuelos Especificos" << endl;
  		cin >> opc;
  		if (opc == 1){
  			listarAero();
		} else if (opc == 2){
			listarDest();
		} else if (opc == 3){
			listarUsers();
		} else if (opc == 4){
			listarMul();
		} else if (opc == 5){
			listarVP();
		} else if (opc == 6){
			listarVE();
		} 
		cout<<"¿Volver a consultar?"<<endl;
  		cout<<"1. Si\n2. No"<<endl;
  		cin >> ctr;
	}
	accionar();
	return 1;
}

void gestionDatos::accionar(){
	int opc;
  	cout << " Bienvenido " << endl;
  	cout << " Elija una opcion: " << endl;
  	cout << "1. Conocer informacion general\n2. Ingresar como Usuario/Aerolinea\n3. Salir" << endl;
  	cin >> opc;
  	if (opc == 1){
  		generaListas();
  	} else if (opc == 2){
  		cout << "Ingrese su ID : ";
  		int id;
  		cin >> id;
  		login(id);
	} else if (opc == 3){
		exit(0);
	}
  
}

#endif
