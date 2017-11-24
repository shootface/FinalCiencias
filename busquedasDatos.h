//importaciones para el control de dichas estructuras
#include "Librerias/listaTemplate.h"
#include "Estructuras/estructuraUsuarios.h"
#include "Estructuras/estructuraAerolinea.h"
#include "Estructuras/estructuraAvion.h"
#include "Estructuras/estructuraVueloEspecifico.h"
#include "Estructuras/estructuraBusquedaItinerarios.h"
#include "Librerias/arbolTemplate.h"
#include "compraDeVuelos.h"

#include <iomanip>
#include <iostream>

#ifndef busquedas
#define bsuquedas
using namespace std;

class busDatos{

    public:
        void busIti(arbinor<airline> airtree,user *us,int day);
        void busOD(arbinor<airline> airtree,user *us,string origen,string destino);
        void listAero(arbinor<airline> airtree);
        void listDest(arbinor<airline> airtree);
        void listUsers(arbinor<user> ustree);
        void listMul(arbinor<airline> airtree);
        void listVPS(arbinor<airline> airtree);
        void listVES(arbinor<airline> airtree);
    private:
};

void busDatos::busIti(arbinor<airline> airtree,user *us,int day){
    int opcion=0;
    int opcionaerolinea=0;
    lista<vueloEspecifico> itinerarios;
    cout << "Desea buscar en una aerolinea especifica o en todas las aerolineas" << endl;
    cout << "1. Para ingresar una aerolinea especifica " << endl;
    cout << "2. Para buscar en todas las aerolineas\n" << endl;
    //Defino donde se van a buscar los trayectos
    cin >> opcionaerolinea;
    //Si se va a buscar en una aerolinea concreta 
    bool rehecho=true;
    while(rehecho){
        int idAirline=0;
    if(opcionaerolinea==1){
        bool hecho = true;
        //Ciclo de busqueda por alguno de los parametros (nombre o codigo)
        while(hecho){
            cout << "1. Si desea buscar por el nombre \n 2. si desea buscar por el codigo de la aerolinea\n" << endl;
            cin >> opcionaerolinea;
            string nameaBuscar;
            //Si se desea buscar por el nombre de la aerolinea
            if(opcionaerolinea==1){
                cout << "Ingrese el nombre de la aerolinea :\n" << endl;
                cin >> nameaBuscar;
                /*
                    se recorre el arbol mediante el metodo inordenCola para agregar
                    cada nodo del arbol a una cola para que asi sea mas facil buscar un dato
                */
                cola<tRelleno> *trT = airtree.inordenCola();
                while (!trT->ColaVacia()){
                    tRelleno tempr = trT->AtenderCola();
                    if(tempr.name==nameaBuscar){
                        idAirline = tempr.id;
                    }
                }
                if(idAirline!=0){
                    cout << "AerolineaEncontrada : " << airtree.buscar(idAirline)->name << endl;
                    itinerarios = airtree.buscar(idAirline)->itinerario;
                    hecho = false;
                }else{
                    cout<< "Ingrese un nombre valido " << endl;
                }
            //Si se desea buscar por el codigo de la aerolinea
            }else if(opcionaerolinea==2){
                cout << "Ingrese el codigo de la aerolinea\n" << endl;
                cin >> idAirline ;
                cout << "Aerolinea : " << airtree.buscar(idAirline)->name << endl;
                itinerarios = airtree.buscar(idAirline)->itinerario;
                if(!itinerarios.lista_vacia()){
                    hecho=false;
                }else{
                    cout << "No se se encontro una aerolinea con ese codigo, revise el dato\n" << endl;
                }
            }
        }
        //Organizacion de los resultados 
        cout << "Como desea organizar los resultados : \n"<< endl;
        cout << "1. Precio \n2. Horario \n3. Duraci�n \n" <<endl;
        cin >> opcion;
        //Organizar por precio
        if(opcion==1){
            cout << "1. Precio adulto \n2. Precio ni�o\n"<< endl;
            cin >> opcion;
            //Organizar por precio adulto
            if(opcion==1){
                vueloEspecifico temp;
                arbinor<itiBus> arbiparaOrganiazar;
                //cout << "tama�o de la lista :" << itinerarios.tamano_lista() << endl;
                airline *aerolineaEncontrada = airtree.buscar(idAirline);
                arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                    temp  = itinerarios.obtenerDato(i);
                    itiBus *apu = new itiBus;
                    //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                    vueloPlaneado *tempp = vuelospla.buscar(temp.idVueloPlaneado);
                    if(tempp->dayWeek==day){
                        apu->idreal = temp.id;
                        apu->id = temp.precioAdulto;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = temp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
                if(arbiparaOrganiazar.reRaiz()==NULL){
                    cout << "No disponemos de vuelos para ese dia en esta aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN" << "DESTINO" << "HI" << "HF" << endl;
                    arbiparaOrganiazar.inordenBusquedaPrecio(arbiparaOrganiazar.reRaiz());
                } 
            //Organizar por precio ni�o
            }else if(opcion==2){
                vueloEspecifico temp;
                arbinor<itiBus> arbiparaOrganiazar;
                //cout << "tama�o de la lista :" << itinerarios.tamano_lista() << endl;
                airline *aerolineaEncontrada = airtree.buscar(idAirline);
                arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                    temp  = itinerarios.obtenerDato(i);
                    itiBus *apu = new itiBus;
                    //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                    vueloPlaneado *tempp = vuelospla.buscar(temp.idVueloPlaneado);
                    if(tempp->dayWeek==day){
                        apu->idreal = temp.id;
                        apu->id = temp.precioNino;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = temp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
                if(arbiparaOrganiazar.reRaiz()==NULL){
                    cout << "No disponemos de vuelos para ese dia en esta aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN" << "DESTINO" << "HI" << "HF" << endl;
                    arbiparaOrganiazar.inordenBusquedaPrecio(arbiparaOrganiazar.reRaiz());  
                } 
            }
        //Organizar por horario
        }else if(opcion==2){
            cout << "1. Ascecendente\n2. Descendenete" << endl;
            cin >> opcion;
            //Organizar horarios de manera ascendente
            if(opcion==1){
                vueloEspecifico temp;
                arbinor<itiBus> arbiparaOrganiazar;
                cout << "tamaño de la lista :" << itinerarios.tamano_lista() << endl;
                airline *aerolineaEncontrada = airtree.buscar(idAirline);
                arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                    temp  = itinerarios.obtenerDato(i);
                    itiBus *apu = new itiBus;
                    //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                    vueloPlaneado *tempp = vuelospla.buscar(temp.idVueloPlaneado);
                    if(tempp->dayWeek==day){ 
                        airline *aerolineaEncontrada = airtree.buscar(idAirline);
                        arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                        vueloPlaneado *tempp = vuelospla.buscar(temp.idVueloPlaneado);
                        apu->idreal = temp.id;
                        apu->id = tempp->hi;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = temp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        apu->precioA = temp.precioAdulto;
                        apu->precioN = temp.precioNino;
                        //Esta de manera desendente
                        //RECORDATORIO SE LE DEBE DAR LA VUELTA AL METODO DE IMPRESION 
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
                //Se imprimen los resultados 
                if(arbiparaOrganiazar.reRaiz()==NULL){
                    cout << "No disponemos de vuelos para ese dia en esta aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO AULTO " << "PRECIO NI�O " << "ORIGEN " << "DESTINO " << "HI" << "HF" << endl;
                    arbiparaOrganiazar.inordenBusquedaHorario(arbiparaOrganiazar.reRaiz());  
                }             
            //Organizacion por horarios de manera descendente
            }else if(opcion==2){
                vueloEspecifico temp;
                arbinor<itiBus> arbiparaOrganiazar;
                //cout << "tama�o de la lista :" << itinerarios.tamano_lista() << endl;
                airline *aerolineaEncontrada = airtree.buscar(idAirline);
                arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                    temp  = itinerarios.obtenerDato(i);
                    itiBus *apu = new itiBus;
                    //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                    vueloPlaneado *tempp = vuelospla.buscar(temp.idVueloPlaneado);
                    if(tempp->dayWeek==day){ 
                        airline *aerolineaEncontrada = airtree.buscar(idAirline);
                        arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                        vueloPlaneado *tempp = vuelospla.buscar(temp.idVueloPlaneado);
                        apu->idreal = temp.id;
                        apu->id = tempp->hi;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = temp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        //Esta de manera desendente
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
                //Se imprimen los resultados 
                if(arbiparaOrganiazar.reRaiz()==NULL){
                    cout << "No disponemos de vuelos para ese dia en esta aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO AULTO " << "PRECIO NI�O " << "ORIGEN " << "DESTINO " << "HI" << "HF" << endl;
                    arbiparaOrganiazar.inordenBusquedaHorario(arbiparaOrganiazar.reRaiz());   
                }
            }
        //Organizar Duracion
        }else if(opcion==3){
                vueloEspecifico temp;
                arbinor<itiBus> arbiparaOrganiazar;
                //cout << "tama�o de la lista :" << itinerarios.tamano_lista() << endl;
                airline *aerolineaEncontrada = airtree.buscar(idAirline);
                arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                    temp  = itinerarios.obtenerDato(i);
                    itiBus *apu = new itiBus;
                    //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                    vueloPlaneado *tempp = vuelospla.buscar(temp.idVueloPlaneado);
                    if(tempp->dayWeek==day){
                        apu->idreal = temp.id;
                        int duracion = tempp->hf-tempp->hi;
                        if(duracion<0){
                            duracion = duracion*-1;
                        }
                        apu->id = duracion;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = temp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
                if(arbiparaOrganiazar.reRaiz()==NULL){
                    cout << "No disponemos de vuelos para ese dia en esta aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO AULTO " << "PRECIO NI�O " << "ORIGEN " << "DESTINO " << "HI" << "HF" << endl;
                    arbiparaOrganiazar.inordenBusquedaDuracion(arbiparaOrganiazar.reRaiz());  
                } 
        }
        cout << "1. Desea realizar otra busqueda\n2. Pasar al carrito\n";
        cin>>opcion;
        if(opcion==2){
            rehecho=false;
        }
    //Se desea buscar en todas las aerolineas
    }else if(opcionaerolinea==2){
        //Organizacion de los resultados 
        cout << "Como desea organizar los resultados : \n"<< endl;
        cout << "1. Precio \n2. Horario \n3. Duraci�n \n" <<endl;
        cin >> opcion;
        //Organizar por precio
        if(opcion==1){
            cout << "1. Precio adulto \n2. Precio ni�o\n"<< endl;
            cin >> opcion;
            if(opcion==1){
                vueloEspecifico tempvp;
                cola<tRelleno> *control = airtree.inordenCola();
                arbinor<itiBus> arbiparaOrganiazar;
                while(!control->ColaVacia()){
                    tRelleno temp = control->AtenderCola();
                    airline *aerolineaEncontrada = airtree.buscar(temp.id);
                    arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                    itinerarios = aerolineaEncontrada->itinerario;
                    for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                        tempvp  = itinerarios.obtenerDato(i);
                        itiBus *apu = new itiBus;
                        //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                        vueloPlaneado *tempp = vuelospla.buscar(tempvp.idVueloPlaneado);
                    if(tempp->dayWeek==day){
                        apu->idreal = tempvp.id;
                        apu->id = tempvp.precioAdulto;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = tempvp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        apu->precioA = tempvp.precioAdulto;
                        apu->precioN = tempvp.precioNino;
                        arbiparaOrganiazar.insertar(apu);
                        }
                    }
                }
                if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaPrecio(arbiparaOrganiazar.reRaiz());
                } 
            }else if(opcion==2){
                vueloEspecifico tempvp;
                cola<tRelleno> *control = airtree.inordenCola();
                arbinor<itiBus> arbiparaOrganiazar;
                while(!control->ColaVacia()){
                    tRelleno temp = control->AtenderCola();
                    airline *aerolineaEncontrada = airtree.buscar(temp.id);
                    arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                    itinerarios = aerolineaEncontrada->itinerario;
                    for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                        tempvp  = itinerarios.obtenerDato(i);
                        itiBus *apu = new itiBus;
                        //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                        vueloPlaneado *tempp = vuelospla.buscar(tempvp.idVueloPlaneado);
                    if(tempp->dayWeek==day){
                        apu->idreal = tempvp.id;
                        apu->id = tempvp.precioNino;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = tempvp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        apu->precioA = tempvp.precioAdulto;
                        apu->precioN = tempvp.precioNino;
                        arbiparaOrganiazar.insertar(apu);
                        }
                    }
                }
                if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaPrecio(arbiparaOrganiazar.reRaiz());
                } 
            }
        //Organizar por Horario
        }else if(opcion==2){
            cout << "1. Asecendente\n2. Descendente" << endl;
            cin >> opcion;
            if(opcion==1){
                vueloEspecifico tempvp;
                cola<tRelleno> *control = airtree.inordenCola();
                arbinor<itiBus> arbiparaOrganiazar;
                while(!control->ColaVacia()){
                    tRelleno temp = control->AtenderCola();
                    airline *aerolineaEncontrada = airtree.buscar(temp.id);
                    arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                    itinerarios = aerolineaEncontrada->itinerario;
                    for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                        tempvp  = itinerarios.obtenerDato(i);
                        itiBus *apu = new itiBus;
                        //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                        vueloPlaneado *tempp = vuelospla.buscar(tempvp.idVueloPlaneado);
                    if(tempp->dayWeek==day){
                        apu->idreal = tempvp.id;
                        apu->id = tempp->hi;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = tempvp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        apu->precioA = tempvp.precioAdulto;
                        apu->precioN = tempvp.precioNino;
                        arbiparaOrganiazar.insertar(apu);
                        }
                    }
                }
                if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaHorario(arbiparaOrganiazar.reRaiz());
                } 
            }else if(opcion==2){
                vueloEspecifico tempvp;
                cola<tRelleno> *control = airtree.inordenCola();
                arbinor<itiBus> arbiparaOrganiazar;
                while(!control->ColaVacia()){
                    tRelleno temp = control->AtenderCola();
                    airline *aerolineaEncontrada = airtree.buscar(temp.id);
                    arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                    itinerarios = aerolineaEncontrada->itinerario;
                    for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                        tempvp  = itinerarios.obtenerDato(i);
                        itiBus *apu = new itiBus;
                        //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                        vueloPlaneado *tempp = vuelospla.buscar(tempvp.idVueloPlaneado);
                    if(tempp->dayWeek==day){
                        apu->idreal = tempvp.id;
                        apu->id = tempp->hi;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = tempvp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        apu->precioA = tempvp.precioAdulto;
                        apu->precioN = tempvp.precioNino;
                        arbiparaOrganiazar.insertar(apu);
                        }
                    }
                }
                if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaHorario(arbiparaOrganiazar.reRaiz());
                } 
            }else{
                cout << "Ingrese una opcion valida" << endl;
            }
        //Organizar por Duracion
        }else if(opcion==3){
            vueloEspecifico tempvp;
                cola<tRelleno> *control = airtree.inordenCola();
                arbinor<itiBus> arbiparaOrganiazar;
                while(!control->ColaVacia()){
                    tRelleno temp = control->AtenderCola();
                    airline *aerolineaEncontrada = airtree.buscar(temp.id);
                    arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                    itinerarios = aerolineaEncontrada->itinerario;
                    for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                        tempvp  = itinerarios.obtenerDato(i);
                        itiBus *apu = new itiBus;
                        //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                        vueloPlaneado *tempp = vuelospla.buscar(tempvp.idVueloPlaneado);
                    if(tempp->dayWeek==day){
                        apu->idreal = tempvp.id;
                        int duracion = tempp->hf-tempp->hi;
                        if(duracion<0){
                            duracion = duracion*-1;
                        }
                        apu->id = duracion;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = tempvp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        apu->precioA = tempvp.precioAdulto;
                        apu->precioN = tempvp.precioNino;
                        arbiparaOrganiazar.insertar(apu);
                        }
                    }
                }
                if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaDuracion(arbiparaOrganiazar.reRaiz());
                } 
        }
        cout << "1. Desea realizar otra busqueda\n2. Pasar al carrito\n";
        cin>>opcion;
        if(opcion==2){
            rehecho=false;
        }
    //Si no se ingreso una opcion valida
    }else{
        cout << "Ingrese una opcion valida\n" << endl;
    }
    }
    cout << "Ingrese el ID del vuelo que sea comprar\n" << endl;
    int id;
    cin >> id;
    compraVuelos tienda;
    tienda.comprar(airtree,day,us);
}
void busDatos::busOD(arbinor<airline> airtree,user *us,string origen,string destino){
    int opcion=0;
    int opcionaerolinea=0;
    bool iv = false;
    lista<vueloEspecifico> itinerarios;
    cout << "Ingrese el numero de pasajero Adultos : \n"<< endl;
    int pasAdul=0;
    cin >> pasAdul;
    cout << "Ingrese el numero de pasajeso Ni�os : \n" << endl;
    int pasNi=0;
    cin >> pasNi;
    cout << "Desea que sea ida y vuelta \n" << endl;
    cout << "1. Si\n2. No" << endl;
    int opcion2=0;
    if(opcion2==1){
        iv = true;
    }
    cout << "Como desea organizar los resultados : \n"<< endl;
    cout << "1. Precio \n2. Horario \n3. Duraci�n \n" <<endl;
    cin >> opcion;
    if(opcion==1){
        cout << "1. Precio adulto \n2. Precio ni�o\n"<< endl;
        cin >> opcion;
        if(opcion==1){
            vueloEspecifico tempvp;
            cola<tRelleno> *control = airtree.inordenCola();
            arbinor<itiBus> arbiparaOrganiazar;
            while(!control->ColaVacia()){
                tRelleno temp = control->AtenderCola();
                airline *aerolineaEncontrada = airtree.buscar(temp.id);
                arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                lista<avion> aviones = aerolineaEncontrada->aviones;
                itinerarios = aerolineaEncontrada->itinerario;
                for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                    tempvp  = itinerarios.obtenerDato(i);
                    itiBus *apu = new itiBus;
                    //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                    vueloPlaneado *tempp = vuelospla.buscar(tempvp.idVueloPlaneado);
                    if(tempp->origin==origen && tempp->posting==destino){
                        apu->idreal = tempvp.id;
                        apu->id = tempvp.precioAdulto;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = tempvp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        apu->precioA = tempvp.precioAdulto;
                        apu->precioN = tempvp.precioNino;
                        arbiparaOrganiazar.insertar(apu);
                        //cout<<"INSERTO"<<endl;
                    }
                }
            }
            if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos con dicho trayecto aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaPrecio(arbiparaOrganiazar.reRaiz());
                    }
        }else if(opcion==2){
            vueloEspecifico tempvp;
            cola<tRelleno> *control = airtree.inordenCola();
            arbinor<itiBus> arbiparaOrganiazar;
            while(!control->ColaVacia()){
                tRelleno temp = control->AtenderCola();
                airline *aerolineaEncontrada = airtree.buscar(temp.id);
                arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                lista<avion> aviones = aerolineaEncontrada->aviones;
                itinerarios = aerolineaEncontrada->itinerario;
                for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                    tempvp  = itinerarios.obtenerDato(i);
                    itiBus *apu = new itiBus;
                    //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                    vueloPlaneado *tempp = vuelospla.buscar(tempvp.idVueloPlaneado);
                    if(tempp->origin==origen && tempp->posting==destino && tempvp.numeroSillasDisponibles>(pasAdul+pasNi)){
                        apu->idreal = tempvp.id;
                        apu->id = tempvp.precioNino;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = tempvp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        apu->precioA = tempvp.precioAdulto;
                        apu->precioN = tempvp.precioNino;
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
            }
            if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaPrecio(arbiparaOrganiazar.reRaiz());
                    }
        }else{
            cout << "Ingrese una opcion valida\n" << endl;
        }        
    }else if(opcion==2){
            vueloEspecifico tempvp;
            cola<tRelleno> *control = airtree.inordenCola();
            arbinor<itiBus> arbiparaOrganiazar;
            while(!control->ColaVacia()){
                tRelleno temp = control->AtenderCola();
                airline *aerolineaEncontrada = airtree.buscar(temp.id);
                arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                lista<avion> aviones = aerolineaEncontrada->aviones;
                itinerarios = aerolineaEncontrada->itinerario;
                for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                    tempvp  = itinerarios.obtenerDato(i);
                    itiBus *apu = new itiBus;
                    //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                    vueloPlaneado *tempp = vuelospla.buscar(tempvp.idVueloPlaneado);
                    if(tempp->origin==origen && tempp->posting==destino){
                        apu->idreal = tempvp.id;
                        apu->id = tempp->hi;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = tempvp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        apu->precioA = tempvp.precioAdulto;
                        apu->precioN = tempvp.precioNino;
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
            }
            if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaHorario(arbiparaOrganiazar.reRaiz());
                    }
    }else if(opcion==3){
            vueloEspecifico tempvp;
            cola<tRelleno> *control = airtree.inordenCola();
            arbinor<itiBus> arbiparaOrganiazar;
            while(!control->ColaVacia()){
                tRelleno temp = control->AtenderCola();
                airline *aerolineaEncontrada = airtree.buscar(temp.id);
                arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                lista<avion> aviones = aerolineaEncontrada->aviones;
                itinerarios = aerolineaEncontrada->itinerario;
                for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                    tempvp  = itinerarios.obtenerDato(i);
                    itiBus *apu = new itiBus;
                    //cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                    vueloPlaneado *tempp = vuelospla.buscar(tempvp.idVueloPlaneado);
                    if(tempp->origin==origen && tempp->posting==destino){
                        apu->idreal = tempvp.id;
                        int duracion = tempp->hf-tempp->hi;
                        if(duracion<0){
                            duracion = duracion*-1;
                        }
                        apu->id = duracion;
                        apu->destino = tempp->posting;
                        apu->origin = tempp->origin;
                        apu->fecha = tempvp.fecha;
                        apu->hf = tempp->hf;
                        apu->hi = tempp->hi;
                        apu->precioA = tempvp.precioAdulto;
                        apu->precioN = tempvp.precioNino;
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
            }
            if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea\n" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaDuracion(arbiparaOrganiazar.reRaiz());
                    }
    }else{
        cout << "Ingrese una opcion valida" << endl;
    }
}

void busDatos::listAero(arbinor<airline> airtree){
	cout<<" LISTADO DE AEROLINEAS "<<endl<<endl;
	cout<<" ID " << " NOMBRE "<< " CUENTA BANCARIA "<< endl;
	airtree.inordenAerolineas(airtree.reRaiz());
}

void busDatos::listDest(arbinor<airline> airtree){
    cola<tRelleno> *control = airtree.inordenCola();
    arbinor<vueloPlaneado> arbiparaOrganiazar;
    while(!control->ColaVacia()){
    	tRelleno temp = control->AtenderCola();
        airline *aerolineaEncontrada = airtree.buscar(temp.id);
        arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
        cout<<"\nDestinos ofrecidos por "<<aerolineaEncontrada->name<<"\n"<<endl<<endl;
        cout << "DESTINO "<< endl;
        vuelospla.inordenVP(vuelospla.reRaiz());
    }
}

void busDatos::listUsers(arbinor<user> ustree){
	cout<<" LISTADO DE USUARIOS "<<endl<<endl;
	cout<<" ID " << " NOMBRE "<< endl;
	ustree.inordenUsuarios(ustree.reRaiz());
}

void busDatos::listMul(arbinor<airline> airtree){

}

void busDatos::listVPS(arbinor<airline> airtree){
	cola<tRelleno> *control = airtree.inordenCola();
    arbinor<vueloPlaneado> arbiparaOrganiazar;
    while(!control->ColaVacia()){
    	tRelleno temp = control->AtenderCola();
        airline *aerolineaEncontrada = airtree.buscar(temp.id);
        arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
        cout<<"\nVuelos Planeados que ofrece "<<aerolineaEncontrada->name<<endl<<endl;
		cout << "ID VUELO " << "ORIGEN " << "DESTINO " << "DIA DE VUELO" << " HI " << "HF " << "NUM SILLAS" << endl;
        vuelospla.inordenVPS(vuelospla.reRaiz());
    }
}

void busDatos::listVES(arbinor<airline> airtree){
	vueloEspecifico tempvp;
	lista<vueloEspecifico> itinerarios;
    cola<tRelleno> *control = airtree.inordenCola();
    while(!control->ColaVacia()){
        tRelleno temp = control->AtenderCola();
        airline *aerolineaEncontrada = airtree.buscar(temp.id);
        arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
        itinerarios = aerolineaEncontrada->itinerario;
        cout<<"\nVuelos Especificos que ofrece "<<aerolineaEncontrada->name<<"\n"<<endl;
        for(int i=0;i<itinerarios.tamano_lista()-1;i++){
            tempvp  = itinerarios.obtenerDato(i);
 			cout<<tempvp.id<<"	"<<tempvp.idVueloPlaneado<<" "<<tempvp.fecha<<"	"<<tempvp.precioAdulto<<" "<<tempvp.precioNino<<endl<<endl;
		}
	}
}
#endif
