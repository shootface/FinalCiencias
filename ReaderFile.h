#include <iostream>
#include <fstream>
#include <stdlib.h>

#ifndef reader
#define reader

using namespace std;

class readerFile{ 
public:
    readerFile(){}
    string readFile(string name);
};

string readFile(string name){
    fstream fs;
    string lectura;
    string lec[100];
    fs.open(name);
    int i=0;
    while (! fs.eof() ) {
        getline (fs,lectura);
        lec[i]=lectura;
        i++;
    }
    lectura = "";
    for(int j=0;j<i;j++){
        lectura = lectura + lec[j];
    }
    fs.close();
    return lectura;
}
#endif