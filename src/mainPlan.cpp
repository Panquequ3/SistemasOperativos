#include <iostream>  
#include "planificador.h"
using namespace std;

int main(int argc, char* argv[]){
    //En caso de reutilizarlo en otra parte
	if(argc != 5){
		cout << "Error. Debe ejecutarse como ./plan  numCores taskPath corePath resultPath" << endl;
		exit(EXIT_FAILURE);
	}
    int numCores = atoi(argv[1]);
    string taskPath = argv[2];
    string corePath = argv[3];
    string resultPath = argv[4];

    coordinator(numCores, taskPath, corePath, resultPath);
    return 0;
}