#include <iostream>
#include <string>
#include <fstream>
#include "core.h"
using namespace std;

float evaluateOperation(string operation, string num1, string num2){
    if(operation == "multiplicacion"){
        return stof(num1)*stof(num2);
    }
    if(operation == "suma"){
        return stof(num1)+stof(num2);
    }
    if(operation == "resta"){
        return stof(num1)-stof(num2);
    }
    if(operation == "division"){
        if(stof(num2)==0){
            cerr << "La division por 0 no esta definida"<<endl;
            exit(EXIT_FAILURE);
        }
        return stof(num1)/stof(num2);
    }
    cerr << "Se a ingresado una operacion no aceptada por el core \n Favor modificar esta"<<endl;
    exit(EXIT_FAILURE);
}
void writeResult(float result,string path,string core){
    string core_path = path+"/"+core+".txt";
    ofstream file(path);
    if(!file.is_open()){
        cout<<"Error al cargar el archivo!!"<<endl;
        exit(EXIT_FAILURE);
    }
    file << result;
    file.close();
}