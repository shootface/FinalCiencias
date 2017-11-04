#include<iostream>
#ifndef estructuraAirline
#define estructuraAirline

using namespace std;
//Estructura para agregar los datos de las aerolineas existentes en el archivo plano de texto 
struct airline{
    int id;
    string name;
    string bankacc;
    airline *izq;
    airline *der;
};
	
#endif
