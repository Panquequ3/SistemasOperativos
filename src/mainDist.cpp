#include <iostream>  
#include "distribuidor.h"
using namespace std;

int main(int argc, char* argv[]){
    //En caso de reutilizarlo en otra parte
	if(argc != 4){
		cout << "Error. Debe ejecutarse como ./dist msg resultPath corePath" << endl;
		exit(EXIT_FAILURE);
	}
    string msg = argv[1];
    string resultPath = argv[2];
    string corePath = argv[3];

    distributeToCore(msg, resultPath, corePath);
    return 0;
}