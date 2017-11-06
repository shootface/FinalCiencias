#include <cstdlib>
#include <iostream>
#include <vector>
#include "colaTemplate.h"

#ifndef arbol
#define arbol

using namespace std;
//Creo un template con el fin de ser capaces de definir una sola libreria
//para controlar la inclusion de datos a un arbol binario organizado con un clave comun

//IMPORTANTE : la clave comun que deben tener todas las estructuras que pretendan utilizar 
//esta libreria debe ser llamada " id " y debe ser de tipo entero para que asi no genere errores
template <class T>
class arbinor{
    T *raiz;
    cola<string> *retorna;
    public:
        arbinor(){
            raiz = NULL;
        }
        //Retorna la raiz de arbol
        T *reRaiz(){return raiz;};
        //Inserta una estructura de tipo T, la estructura se crea en ReaderFile.h
        int insertar (T *u);
        //Metodo encargado de buscar en que posicion se debe agregar un elemento al arbol
        T *buscar_arbol(T *u, T *p, T *q);
        //Recibe un " id " con el fin de buscarlo en la estructura del arbol y devolver toda la estructura
        T *buscar(int id);
        void inorden(T *p);
        cola<string> *inordenCola();
    private:
    	cola<string> *inordenCola(T *p);
};

template <class T>
int arbinor<T>::insertar(T *u){
    T *q;
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

template <class T>
T *arbinor<T>::buscar_arbol(T *u,T *p,T *q){
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

template <class T>
T *arbinor<T>::buscar(int id){
    T *actual = reRaiz();
    while(actual!=NULL) {
        if(id == actual->id) return actual;
            else if(id < actual->id) actual = actual->izq;
            else if(id > actual->id) actual = actual->der;
    }
    return NULL;
}

template <class T>
void arbinor<T>::inorden(T *p){
    if (p!=NULL){
        inorden(p->izq);
        cout<<p->id<< " " <<p->name<<endl;
        inorden(p->der);}
}

template <class T>
cola<string> *arbinor<T>::inordenCola(){
	retorna = new cola<string>;
	return inordenCola(raiz);	
}

template <class T>
cola<string> *arbinor<T>::inordenCola(T *p){
	if(p!=NULL){
		inordenCola(p->izq);
		retorna->InsCola(p->name);
		inordenCola(p->der);
		return retorna;
	}
}
#endif
