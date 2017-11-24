//importaciones para el control de dichas estructuras
#include "Librerias/listaTemplate.h"
#include "Estructuras/estructuraUsuarios.h"
#include "Estructuras/estructuraAerolinea.h"
#include "Estructuras/estructuraAvion.h"
#include "Estructuras/estructuraVueloEspecifico.h"
#include "Estructuras/estructuraBusquedaItinerarios.h"
#include "Librerias/arbolTemplate.h"
#include "compraDeVuelos.h"

#ifndef busquedas
#define bsuquedas
using namespace std;

class busDatos{

    public:
        void busIti(arbinor<airline> airtree,user *us,int day);
        void busOD(arbinor<airline> airtree,user *us,string origen,string destino);
    private:
};

void busDatos::busIti(arbinor<airline> airtree,user *us,int day){
    int opcion=0;
    int opcionaerolinea=0;
    lista<vueloEspecifico> itinerarios;
    cout << "Desea buscar en una aerolinea especifica o en todas las aerolineas" << endl;
    cout << "1. Para ingresar una aerolinea especifica " << endl;
    cout << "2. Para buscar en todas las aerolineas " << endl;
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
            cout << "1. si desea buscar por el nombre \n 2. si desea buscar por el codigo de la aerolinea" << endl;
            cin >> opcionaerolinea;
            string nameaBuscar;
            //Si se desea buscar por el nombre de la aerolinea
            if(opcionaerolinea==1){
                cout << "Ingrese el nombre de la aerolinea :" << endl;
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
                    cout<< "ingrese un nombre valido " << endl;
                }
            //Si se desea buscar por el codigo de la aerolinea
            }else if(opcionaerolinea==2){
                cout << "ingrese el codigo de la aerolinea" << endl;
                cin >> idAirline ;
                cout << "Aerolinea : " << airtree.buscar(idAirline)->name << endl;
                itinerarios = airtree.buscar(idAirline)->itinerario;
                if(!itinerarios.lista_vacia()){
                    hecho=false;
                }else{
                    cout << "No se se encontro una aerolinea con ese codigo, revise el dato" << endl;
                }
            }
        }
        //Organizacion de los resultados 
        cout << "Como desea organizar los resultados : "<< endl;
        cout << "1. Precio \n2. Horario \n3. Duración \n" <<endl;
        cin >> opcion;
        //Organizar por precio
        if(opcion==1){
            cout << "1.Precio adulto \n2.Precio niño"<< endl;
            cin >> opcion;
            //Organizar por precio adulto
            if(opcion==1){
                vueloEspecifico temp;
                arbinor<itiBus> arbiparaOrganiazar;
                //cout << "tamaño de la lista :" << itinerarios.tamano_lista() << endl;
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
                    cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN" << "DESTINO" << "HI" << "HF" << endl;
                    arbiparaOrganiazar.inordenBusquedaPrecio(arbiparaOrganiazar.reRaiz());
                } 
            //Organizar por precio niño
            }else if(opcion==2){
                vueloEspecifico temp;
                arbinor<itiBus> arbiparaOrganiazar;
                //cout << "tamaño de la lista :" << itinerarios.tamano_lista() << endl;
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
                    cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN" << "DESTINO" << "HI" << "HF" << endl;
                    arbiparaOrganiazar.inordenBusquedaPrecio(arbiparaOrganiazar.reRaiz());  
                } 
            }
        //Organizar por horario
        }else if(opcion==2){
            cout << "1.Asecendente\n2.Desendenete" << endl;
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
                    cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
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
                    cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO AULTO " << "PRECIO NIÑO " << "ORIGEN " << "DESTINO " << "HI" << "HF" << endl;
                    arbiparaOrganiazar.inordenBusquedaHorario(arbiparaOrganiazar.reRaiz());  
                }             
            //Organizacion por horarios de manera descendente
            }else if(opcion==2){
                vueloEspecifico temp;
                arbinor<itiBus> arbiparaOrganiazar;
                //cout << "tamaño de la lista :" << itinerarios.tamano_lista() << endl;
                airline *aerolineaEncontrada = airtree.buscar(idAirline);
                arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                    temp  = itinerarios.obtenerDato(i);
                    itiBus *apu = new itiBus;
                    cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
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
                    cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO AULTO " << "PRECIO NIÑO " << "ORIGEN " << "DESTINO " << "HI" << "HF" << endl;
                    arbiparaOrganiazar.inordenBusquedaHorario(arbiparaOrganiazar.reRaiz());   
                }
            }
        //Organizar Duracion
        }else if(opcion==3){
                vueloEspecifico temp;
                arbinor<itiBus> arbiparaOrganiazar;
                //cout << "tamaño de la lista :" << itinerarios.tamano_lista() << endl;
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
                    cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO AULTO " << "PRECIO NIÑO " << "ORIGEN " << "DESTINO " << "HI" << "HF" << endl;
                    arbiparaOrganiazar.inordenBusquedaDuracion(arbiparaOrganiazar.reRaiz());  
                } 
        }
        cout << "1. Desea realizar otra busqueda\n2.Pasar al carrito";
        cin>>opcion;
        if(opcion==2){
            rehecho=false;
        }
    //Se desea buscar en todas las aerolineas
    }else if(opcionaerolinea==2){
        //Organizacion de los resultados 
        cout << "Como desea organizar los resultados : "<< endl;
        cout << "1. Precio \n2. Horario \n3. Duración \n" <<endl;
        cin >> opcion;
        //Organizar por precio
        if(opcion==1){
            cout << "1.Precio adulto \n2.Precio niño"<< endl;
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
                        arbiparaOrganiazar.insertar(apu);
                        }
                    }
                }
                if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
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
                        arbiparaOrganiazar.insertar(apu);
                        }
                    }
                }
                if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaPrecio(arbiparaOrganiazar.reRaiz());
                } 
            }
        //Organizar por Horario
        }else if(opcion==2){
            cout << "1.Asecendente\n2.Desendenete" << endl;
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
                cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
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
                cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaHorario(arbiparaOrganiazar.reRaiz());
                } 
            }else{
                cout << "ingrese una opcion valida" << endl;
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
                        arbiparaOrganiazar.insertar(apu);
                        }
                    }
                }
                if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaDuracion(arbiparaOrganiazar.reRaiz());
                } 
        }
        cout << "1. Desea realizar otra busqueda\n2.Pasar al carrito";
        cin>>opcion;
        if(opcion==2){
            rehecho=false;
        }
    //Si no se ingreso una opcion valida
    }else{
        cout << "ingrese una opcion valida" << endl;
    }
    }
    cout << "Ingrese el ID del vuelo que sea comprar" << endl;
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
    cout << "Ingrese el numero de pasajero Adultos : "<< endl;
    int pasAdul=0;
    cin >> pasAdul;
    cout << "Ingrse el numero de pasajeso Niños : " << endl;
    int pasNi=0;
    cin >> pasNi;
    cout << "Desea que sea iba y vuelta " << endl;
    cout << "1.si\n2.no" << endl;
    int opcion2=0;
    if(opcion2==1){
        iv = true;
    }
    cout << "Como desea organizar los resultados : "<< endl;
    cout << "1. Precio \n2. Horario \n3. Duración \n" <<endl;
    cin >> opcion;
    if(opcion==1){
        cout << "1.Precio adulto \n2.Precio niño"<< endl;
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
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
            }
            if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
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
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
            }
            if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaPrecio(arbiparaOrganiazar.reRaiz());
                    }
        }else{
            cout << "ingrese una opcion valida" << endl;
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
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
            }
            if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
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
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
            }
            if(arbiparaOrganiazar.reRaiz()==NULL){
                cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
                }else {
                    cout << "ID VUELO " << "FECHA " << "PRECIO "<< "ORIGEN " << "DESTINO " << "HI " << "HF " << endl;
                    arbiparaOrganiazar.inordenBusquedaDuracion(arbiparaOrganiazar.reRaiz());
                    }
    }else{
        cout << "ingrese una opcion valida" << endl;
    }
}
#endif