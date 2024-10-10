#include <iostream>
#include "conteoParalelo.h"
using namespace std;

int main(int argc, char* argv[]){
    //En caso de reutilizarlo en otra parte
	if(argc != 7){
		cout << "Error. Debe ejecutarse como ./paralelo nHilos pathP pathR extension pathStopWord pathTemp" << endl;
		exit(EXIT_FAILURE);
	}
    int numTh = atoi(argv[1]);
    string pathP = argv[2];
    string pathR = argv[3];
    string ext = argv[4];
    string stopWord = argv[5];
    cout << stopWord << endl;
    string temp = argv[6];

    //ej : assignThreads(4, "./data/procesar", "./data/resultados","txt", "./data/stop_word.txt", "./data/temporal");
    //assignThreads(numTh, pathP, pathR, ext, stopWord, temp);
    return 0;
}