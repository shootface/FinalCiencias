//importaciones para el control de dichas estructuras
#include "Librerias/listaTemplate.h"
#include "Estructuras/estructuraUsuarios.h"
#include "Estructuras/estructuraAerolinea.h"
#include "Estructuras/estructuraAvion.h"
#include "Estructuras/estructuraVueloEspecifico.h"
#include "Estructuras/estructuraBusquedaItinerarios.h"
#include "Librerias/arbolTemplate.h"

#ifndef busquedas
#define bsuquedas
using namespace std;

class busDatos{

    public:
        void busIti(arbinor<airline> airtree,int day);
    private:
};

void busDatos::busIti(arbinor<airline> airtree,int day){
    int opcion=0;
    int opcionaerolinea=0;
    lista<vueloEspecifico> itinerarios;
    cout << "Desea buscar en una aerolinea especifica o en todas las aerolineas" << endl;
    cout << "1. Para ingresar una aerolinea especifica " << endl;
    cout << "2. Para buscar en todas las aerolineas " << endl;
    //Defino donde se van a buscar los trayectos
    cin >> opcionaerolinea;
    //Si se va a buscar en una aerolinea concreta 
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
                cola<tRelleno> *trT = airtree.inordenCola();
                while (!trT->ColaVacia()){
                    tRelleno tempr = trT->AtenderCola();
                    cout << "nombre prueba : " << tempr.name << endl;
                    if(tempr.name==nameaBuscar){
                        idAirline = tempr.id;
                    }
                }
                if(idAirline!=0){
                    cout << "Aerolinea : " << airtree.buscar(idAirline)->name << endl;
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
                hecho=false;
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
                cout << "tamaño de la lista :" << itinerarios.tamano_lista() << endl;
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
                    arbiparaOrganiazar.inordenBusqueda(arbiparaOrganiazar.reRaiz());  
                } 
            //Organizar por precio niño
            }else if(opcion==2){
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
                        apu->idreal = temp.id;
                        apu->id = temp.precioNino;
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
                if(arbiparaOrganiazar.reRaiz()==NULL){
                    cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
                }else {
                    arbiparaOrganiazar.inorden(arbiparaOrganiazar.reRaiz());  
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
                        apu->idreal = temp.id;
                        airline *aerolineaEncontrada = airtree.buscar(idAirline);
                        arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                        vueloPlaneado *tempp = vuelospla.buscar(temp.idVueloPlaneado);
                        apu->id = tempp->hi;
                        //Esta de manera desendente
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
                //Se imprimen los resultados 
                if(arbiparaOrganiazar.reRaiz()==NULL){
                    cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
                }else {
                    arbiparaOrganiazar.inorden(arbiparaOrganiazar.reRaiz());  
                }             
            //Organizacion por horarios de manera descendente
            }else if(opcion==2){
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
                        apu->idreal = temp.id;
                        airline *aerolineaEncontrada = airtree.buscar(idAirline);
                        arbinor<vueloPlaneado> vuelospla = aerolineaEncontrada->trayectos;
                        vueloPlaneado *tempp = vuelospla.buscar(temp.idVueloPlaneado);
                        apu->id = tempp->hi;
                        //Esta de manera desendente
                        arbiparaOrganiazar.insertar(apu);
                    }
                }
                if(arbiparaOrganiazar.reRaiz()==NULL){
                    cout << "No disponemos de vuelos para ese dia en esta aerolinea" << endl;
                }else {
                    arbiparaOrganiazar.inorden(arbiparaOrganiazar.reRaiz());  
                }
            }
        }
    }else if(opcion==2){

        //arbinor<vueloEspecifico> * 
    }
    //airline *airtemp = 
}
#endif