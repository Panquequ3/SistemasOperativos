#include <iostream>
#include "conteoParalelo.h"
#include <chrono> //para la medición del tiempo
using namespace std;

int main(int argc, char* argv[]){
    // inicio de la medición
    auto start = chrono::high_resolution_clock::now();

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
    // para finalizar el tiempo de medición
    auto end = chrono::high_resolution_clock::now();

    // calculamos la duración
    // chrono::duration -> representa un intervalo de tiempo , definte <tipoDato, unidadTiempo>
    chrono::duration<double, milli> duration = end - start;
    cout << "La duración fue " << duration.count() << " ms " <<  endl;
    // Duración en segundos
    chrono::duration<double> duration_s = end - start;
    cout << "Duración en segundos: " << duration_s.count() << " s" << endl;
    return 0;
}