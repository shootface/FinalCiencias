#include <iostream>
#include "ReaderFile.h"
#include "Arboltemplate.h"
#include "estructuraUsuarios.h"

using namespace std;


int main(){
    readerFile<user> rd;
    string name = "usuarios.txt";
    rd.readFile(name); 
    rd.organizarUsuarios(rd.getLectura());
    arbinor<user> arbolUser = rd.getArbol();
    //arbolUser.inorden(arbolUser.reRaiz());
    user *usfound = arbolUser.buscar(30102948);
    cout << "Name : " << usfound -> name  << "ID :"<< usfound -> id << endl;
}