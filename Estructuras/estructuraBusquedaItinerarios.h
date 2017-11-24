#include "iostream"
#ifndef estuBusqueda
#define estuBusqueda

using namespace std;
struct itiBus{
    int idreal;
    int id;
    int hi;
    int hf;
    int precioA;
    int precioN;
    string destino;
    string origin;
    string fecha;
    itiBus *izq;
    itiBus *der;
};
#endif