#include <cstdlib>
#include <iostream>

#define NULL __null
#ifndef arbol
#define arbol

using namespace std;

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
        user *reRaiz(){return raiz;};
        int insertar (user *u);
        user *buscar_arbol(user *u, user *p,user *q);
        user *buscar(int id,user *p,user *q);
        user *buscarU(int ip);
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
user *arbinor::buscar(int id,user *p,user *q){
    /*if (p==NULL) return NULL;
	if (id < p->id){
              q=p;
              p=p->izq;
	          q=buscar(id,p,q);
              return q;
    }
	else if (id >p->id){
		q=p;
		p=p->der;
		q =buscar(id,p,q);
		return q;}
           else return q;*/
    user *actual = reRaiz();
    while(actual!=NULL) {
        if(id == actual->id) return actual; /* dato encontrado  (2) */
            else if(id < actual->id) actual = actual->izq;  /* (3) */
            else if(id > actual->id) actual = actual->der; /* (4) */
    }
    cout<< "no existe";
    return NULL;
}
void arbinor::inorden(user *p){
    if (p!=NULL){
        inorden(p->izq);
        cout<<p->id<<endl;
        inorden(p->der);}
}
#endif