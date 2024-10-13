#include <iostream>
#include "conteoParalelo.h"
using namespace std;

int main(int argc, char* argv[]){
    //En caso de reutilizarlo en otra parte
	if(argc != 8){
		cout << "Error. Debe ejecutarse como ./paralelo nHilos pathP pathR extension pathStopWord pathTemp mapPath" << endl;
		exit(EXIT_FAILURE);
	}
    int numTh = atoi(argv[1]);
    string pathP = argv[2];
    string pathR = argv[3];
    string ext = argv[4];
    string stopWord = argv[5];
    string temp = argv[6];
    string map = argv[7];

    //ej : assignThreads(4, "./data/procesar", "./data/resultados","txt", "./data/stop_word.txt", "./data/temporal", "./data/map.txt");
    assignThreads(numTh, pathP, pathR, ext, stopWord, temp, map);
    return 0;
}