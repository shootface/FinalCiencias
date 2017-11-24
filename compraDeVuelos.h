//Importaciones para control de datos
#include "iostream"
#include "WriterFile.h"
#include "ReaderFile.h"
#include "Librerias/listaTemplate.h"
#include "Estructuras/estructuraUsuarios.h"
#include "Estructuras/estructuraAerolinea.h"
#include "Estructuras/estructuraAvion.h"
#include "Estructuras/estructuraVueloEspecifico.h"
#include "Estructuras/estructuraBusquedaItinerarios.h"
#include "Librerias/arbolTemplate.h"

#ifndef compra
#define compra
using namespace std;

class compraVuelos{
    public:
        void comprar(arbinor<airline> airtree,int id,user *us);
    private:

};
 void compraVuelos::comprar(arbinor<airline> airtree,int id,user *us){
     cola<tRelleno> *colaAerolineas = airtree.inordenCola();
     int idAirline=0;
     int idVp=0;
     while(!colaAerolineas->ColaVacia()){
        tRelleno temptr = colaAerolineas->AtenderCola();
        airline *tempAir = airtree.buscar(temptr.id);
        lista<vueloEspecifico> itinerario = tempAir->itinerario; 
        lista<avion> aviones = tempAir->aviones;
        for(int i=0;i<itinerario.tamano_lista()-1;i++){
            vueloEspecifico temp;
            temp = itinerario.obtenerDato(i);
            if(temp.id==id){
                idVp = temp.idVueloPlaneado;
                idAirline = temptr.id;
            }
        }
     }
    
 }
#endif
