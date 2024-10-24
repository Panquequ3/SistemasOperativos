#include <iostream>
#include "core.h"
using namespace std;

int main(int argc, char* argv[]){
    if(argc!=6){
        cout << "Error. Debe ejecutarse como ./core operacion num1 num2 id_core path_cores"<<endl;
    }
    string operation = argv[1];
    string num1 = argv[2];
    string num2 = argv[3];
    string core = argv[4];
    string path = argv[5];

    float result = evaluateOperation(operation,num1,num2);
    writeResult(result,path,core);
    return 0;
}