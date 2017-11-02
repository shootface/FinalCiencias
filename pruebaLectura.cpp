#include <iostream>
#include <time.h>
#include <fstream>
#include "ReaderFile.h"

using namespace std;


int main(){
    string name = "usuarios.txt";
    name = readFile(name);
    cout << "dato : " << name << endl; 
}