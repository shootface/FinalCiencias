#include<iostream>
#include <fstream>
#include "ReaderFile.h"
#ifndef writer
#define writer

using namespace std;

class writerFile{
public:
    int write(string name,string dato);
};
int writerFile::write(string name,string dato){
    readerFile<string> rd;
    ofstream salida;
    rd.readFile(name);
    vector<string> vc = rd.getLectura();
    salida.open(name);
    for(int i=0;i<vc.size()-1;i++){
        salida << vc[i] << endl;
    }
    salida << dato << endl;
    salida.close();
}
#endif