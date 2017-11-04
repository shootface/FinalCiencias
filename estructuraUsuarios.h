#include<iostream>
#ifndef estructuraUser
#define estructuraUser

using namespace std;
//Estructura para agregar los datos de los usuarios alojados en el archivo plano de texto 
struct user{
    int id;
    int age;
    string name;
    string lastname;
    char sex;
    user *izq;
    user *der;
};
#endif