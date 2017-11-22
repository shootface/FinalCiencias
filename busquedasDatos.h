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
        void busIti(arbinor<airline> airtree);
    private:
};

void busDatos::busIti(arbinor<airline> airtree){
    int opcion=0;
    int opcionaerolinea=0;
    lista<vueloEspecifico> itinerarios;
    cout << "Desea buscar en una aerolinea especifica o en todas las aerolineas" << endl;
    cout << "1. Para ingresar una aerolinea especifica " << endl;
    cout << "2. Para buscar en todas las aerolineas " << endl;
    //Defino donde se van a buscar los trayectos
    cin >> opcionaerolinea;
    //Si se va a buscar en una aerolinea concreta 
    if(opcionaerolinea==1){
        bool hecho = true;
        while(hecho){
            cout << "1. si desea buscar por el nombre \n 2. si desea buscar por el codigo de la aerolinea" << endl;
            cin >> opcionaerolinea;
            string nameaBuscar;
            int idAirline=0;
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
            }else if(opcionaerolinea==2){
                cout << "ingrese el codigo de la aerolinea" << endl;
                cin >> idAirline ;
                cout << "Aerolinea : " << airtree.buscar(idAirline)->name << endl;
                itinerarios = airtree.buscar(idAirline)->itinerario;
                hecho=false;
            }
        }
        cout << "Como desea organizar los resultados : "<< endl;
        cout << "1. Precio \n2. Horario \n3. Duración \n" <<endl;
        cin >> opcion;
        if(opcion==1){
            cout << "1.Precio adulto \n2.Precio niño"<< endl;
            cin >> opcion;
            if(opcion==1){
                vueloEspecifico temp;
                itiBus apu;
                itiBus *aputemp;
                arbinor<itiBus> arbiparaOrganiazar;
                cout << "tamaño de la lista :" << itinerarios.tamano_lista() << endl;
                for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                    temp  = itinerarios.obtenerDato(i);
                    cout << "ID del VE : "<< temp.id << "Precio : "<< temp.precioAdulto<< endl;
                    apu.idreal = temp.id;
                    //cout << "APUNTO REAL" << endl;
                    apu.id = temp.precioAdulto;
                    //cout << "APUNTO PRECIO" << endl;
                    aputemp = &apu;
                    arbiparaOrganiazar.insertar(aputemp);
                }
                arbiparaOrganiazar.inorden(arbiparaOrganiazar.reRaiz());
            }else if(opcion==2){
                vueloEspecifico temp;
                itiBus *apu;
                arbinor<itiBus> arbiparaOrganiazar;
                cout << "tamaño de la lista :" << itinerarios.tamano_lista() << endl;
                for(int i=0;i<itinerarios.tamano_lista()-1;i++){
                    temp  = itinerarios.obtenerDato(i);
                    cout << "ID del VE : "<< temp.id << endl;
                    /*apu->idreal = temp.id;
                    apu->id = temp.precioNino;
                    arbiparaOrganiazar.insertar(apu);*/
                }
                //arbiparaOrganiazar.inorden(arbiparaOrganiazar.reRaiz());
            }
        }else if(opcion==2){
            cout << "1.Asecendente\n2.Desendenete" << endl;
            cin >> opcion;
        }
    }
    if(opcion==1){

        //arbinor<vueloEspecifico> * 
    }
    //airline *airtemp = 
}
#endif