#include <vector>
#include "colaTemplate.h"
#include "ReaderFile.h"
#include "Arboltemplate.h"

#ifndef trayectosControl
#define trayectosControl

class controlTrayectos{
public:
    arbinor<vuelopla> *tra;
    controlTrayectos(arbinor<vuelopla> *trayectos){
        tra = trayectos;
    }
    //Ingresa un vuelo planeado al plan de trayectos semanales
    arbinor<vuelopla> *getTrayectos(){return tra;};
    int agregarVueloP(vuelopla vp);
    cola<vuelopla> consultar(int day);
private:
    void guardarDatos(vuelopla vp);
};
int agregarVueloP(vuelopla vp){
    
}
#endif