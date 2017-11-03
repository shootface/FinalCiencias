#include <iostream>
#include <fstream>
#include <vector>
#include "ArbolUser.h"

#ifndef reader
#define reader

using namespace std;

class readerFile{    
public:
    arbinor arbolUser;
    readerFile(){}
    void readFile(string name); 
    arbinor getArbol(){return arbolUser;};
private:
    void organizarUsuarios(string lec2[]);
    void split(string user1);
    void crearUsuario(vector<string> users);
};
void readerFile::readFile(string name){
    string lectura;
    fstream fs;
    string lec[100];
    fs.open(name);
    int i=0;
    while (! fs.eof() ) {
        getline (fs,lectura);
        lec[i]=lectura;
        i++;
    }
    fs.close();
    organizarUsuarios(lec);
}
void readerFile::organizarUsuarios(string lec2[]){
    string temp;
    for(int i=0;i<100;i++){
        temp = lec2[i];
        split(temp);
    }
}
void readerFile::split(string user1){
    string temp;
    vector<string> usertemp;
    vector<string> usertemp2;
    int found;
    cout << "Llegada : "<< user1 << endl;
    while(found!=-1){
        found = user1.find("/");
        temp = user1.substr(0,found); 
        usertemp.push_back(temp);
        user1 = user1.substr(found+1,user1.size());
    }
    /*for(int i=0;i<5;i++){
        cout << usertemp[i] << endl;
    }*/
    found = NULL;
    crearUsuario(usertemp);
    usertemp.erase(usertemp.begin(),usertemp.end());
}
void readerFile::crearUsuario(vector<string> users){
    user *u = new user;
    u -> name = users[0];
    u -> lastname = users[1];
    u -> id = stoi (users[2],nullptr,0);
    u -> sex = users[3][0];
    arbolUser.insertar(u);
}
#endif