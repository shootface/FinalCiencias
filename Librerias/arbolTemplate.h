#include <iostream>
#include <vector>

#include "colaTemplate.h"

#include "../Estructuras/estructuraRelleno.h"
#include "../Estructuras/estructuraVueloPlaneado.h"

#ifndef ARBOLTEMPLATE_H
#define ARBOLTEMPLATE_H

using namespace std;
/*
	Creo un template con el fin de ser capaces de definir una sola libreria
	para controlar la inclusion de datos a un arbol binario organizado con un clave comun
	
	IMPORTANTE : la clave comun que deben tener todas las estructuras que pretendan utilizar
	esta libreria debe ser llamada " id " y debe ser de tipo entero para que asi no genere errores
*/
template <class T>
class arbinor{
    T *raiz;
    cola<tRelleno> *retorna;
    cola<int> *ids;
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
        void inordenBusquedaPrecio(T *p);
        void inordenBusquedaHorario(T *p);
        void inordenBusquedaDuracion(T *p);
        void inordenAerolineas(T *p);
        void inordenUsuarios(T *p);
        void inordenVP(T *p);
        void inordenVPS(T *p);
        cola<tRelleno> *inordenCola();
        cola<int> *inOrdenV();
        cola<int> *inOrdenV(T *p);
    private:
        cola<tRelleno> *inordenCola(T *p);

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
        cout<<p->id<<endl;
        inorden(p->der);
    }
}

template <class T>
void arbinor<T>::inordenAerolineas(T *p){
    if (p!=NULL){
        inordenAerolineas(p->izq);
        cout<<p->id<<" "<<p->name<<" "<<p->bankacc<<endl;
        inordenAerolineas(p->der);
    }
}
template <class T>
void arbinor<T>::inordenUsuarios(T *p){
    if (p!=NULL){
        inordenUsuarios(p->izq);
        cout<<p->id<<" "<<p->name<<" "<<p->lastname<<endl;
        inordenUsuarios(p->der);
    }
}
template <class T>
void arbinor<T>::inordenVP(T *p){
    if (p!=NULL){
        inordenVP(p->izq);
        cout<<p->posting<<endl;
        inordenVP(p->der);
    }
}
template <class T>
void arbinor<T>::inordenVPS(T *p){
    if (p!=NULL){
        inordenVPS(p->izq);
        cout<<p->id<<" "<<p->origin<<" "<<p->posting<<" "<<p->dayWeek<<" "<<p->hi<<" "<<p->hf<<" "<<p->numS<<endl;
        inordenVPS(p->der);
    }
}
template <class T>
void arbinor<T>::inordenBusquedaPrecio(T *p){
    if (p!=NULL){
        inordenBusquedaPrecio(p->izq);
        cout<<p->idreal<<" "<<p->fecha<<" "<<p->id<<" "<<p->origin<<" "<<p->destino<<" "<<p->hi<<" "<<p->hf<<endl;
        inordenBusquedaPrecio(p->der);
    }
}
template <class T>
void arbinor<T>::inordenBusquedaHorario(T *p){
    if (p!=NULL){
        inordenBusquedaHorario(p->izq);
        cout<<p->idreal<<" "<<p->fecha<<" "<<p->precioA <<" "<<p->precioN <<" "<<p->origin<<" "<<p->destino<<" "<<p->id<<" "<<p->hf<<endl;
        inordenBusquedaHorario(p->der);
    }
}
template <class T>
void arbinor<T>::inordenBusquedaDuracion(T *p){
    if (p!=NULL){
        inordenBusquedaDuracion(p->izq);
        cout<<p->idreal<<" "<<p->fecha<<" "<<p->precioA <<" "<<p->precioN <<" "<<p->origin<<" "<<p->destino<<" "<<p->hi<<" "<<p->hf<<" "<< p->id<<endl;
        inordenBusquedaDuracion(p->der);
    }
}

template <class T>
cola<tRelleno> *arbinor<T>::inordenCola(){
	retorna = new cola<tRelleno>;
	return inordenCola(raiz);
}

template <class T>
cola<tRelleno> *arbinor<T>::inordenCola(T *p){
    tRelleno r;
	if(p!=NULL){
        inordenCola(p->izq);
        r.id = p -> id;
        r.name = p -> name;
		retorna->InsCola(r);
		inordenCola(p->der);
		return retorna;
	}
}

template <class T>
cola<int> *arbinor<T>::inOrdenV(){
    ids = new cola<int>;
    return inOrdenV(raiz);
}

template <class T>
cola<int> *arbinor<T>::inOrdenV(T *p){
    if (p!=NULL){
        inOrdenV(p->izq);
        cout << "ENTONCES :" << p->id << endl;
        ids->InsCola(p->id);
        inOrdenV(p->der);
        return ids;
    }
}

#endif#endif
