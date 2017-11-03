#include <iostream>
#include "ReaderFile.h"
#include "ArbolUser.h"

using namespace std;


int main(){
    readerFile rd;
    string name = "usuarios.txt";
    rd.readFile(name); 
    arbinor arbolUser = rd.getArbol();
    //arbolUser.inorden(arbolUser.reRaiz());
    user *usfound = arbolUser.buscar(30102948,arbolUser.reRaiz(),arbolUser.reRaiz());
    cout << "Name : " << usfound -> name  << "ID :"<< usfound -> id << endl;
}