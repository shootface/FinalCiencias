#include <cstdlib>
#include <iostream>


#define NULL __null
#ifndef arbol
#define arbol

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

class arbinor{
    user *raiz;
    public:
        arbinor(){
            raiz = NULL;
        }
        //Retorna la raiz de arbol
        user *reRaiz(){return raiz;};
        //inserta una estructura de usuario, la estructua de usuario se crea en ReaderFile.h
        int insertar (user *u);
        //Metodo encargado de buscar en que posicion se debe agregar un elemento al arbol
        user *buscar_arbol(user *u, user *p,user *q);
        //Recibe un numero de documento con el fin de buscarlo en la estructura del arbol y devolver toda la estructura
        user *buscar(int id);
        void inorden(user *p);
 };

int arbinor::insertar(user *u){
    user *q;
    if (raiz == NULL){
    raiz = u;
    raiz->izq=raiz->der=NULL;
    return 0;
    }
    q = buscar_arbol(u,raiz,NULL);
    if (q==NULL){
        return -1;
    }
    u->izq=u->der=NULL;
    if (u->id < q->id){
        q->izq=u;
    }else   q->der=u;
    return 0;
}
user *arbinor::buscar_arbol(user *u,user *p,user *q){
    if (p==NULL){
        return q;
    } 
    if (u->id < p->id){
        q=p;
        q=buscar_arbol(u,p->izq,q);
        return q;
    }else if (u->id > p->id) {
        q=p;
        q=buscar_arbol(u,p->der,q);
        return q;
    }else return NULL;
}
user *arbinor::buscar(int id){
    user *actual = reRaiz();
    while(actual!=NULL) {
        if(id == actual->id) return actual;
            else if(id < actual->id) actual = actual->izq;
            else if(id > actual->id) actual = actual->der;
    }
    return NULL;
}
void arbinor::inorden(user *p){
    if (p!=NULL){
        inorden(p->izq);
        cout<<p->id<<endl;
        inorden(p->der);}
}
#endif