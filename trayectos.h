#include <vector>
#include "colaTemplate.h"
#include "ReaderFile.h"
#include "Arboltemplate.h"

#ifndef trayectosControl
#define trayectosControl

class controlTrayectos{
public:
    string filename;
    arbinor<vuelopla> *tra;
    controlTrayectos(string name,arbinor<vuelopla> *trayectos){
        filename = name;
        tra = trayectos;
    }
    //Ingresa un vuelo planeado al plan de trayectos semanales
    int agregarVueloP(vuelopla vp);
    cola<vuelopla> consultar(int day);
private:
    void guardarDatos(vuelopla vp);
};
int agregarVueloP(vuelopla vp){
    
}
#endif