#include <iostream>
#include <vector>
#include <string>
#include <chrono> //para la medición del tiempo
#include "ejecutador.h"
using namespace std;

void ejecute(int thread, string cmd, int repeats, string dataPath){
    string command = "./paralelo " + to_string(thread) + " " + cmd;
    cout << "toi akiii" << endl;
    for(int i = 0; i < repeats; i++){
        cout << "cantidad de hilos usados: " << thread << endl;

        // inicio de la medición
        auto start = chrono::high_resolution_clock::now();

        system(command.c_str());

        // para finalizar el tiempo de medición
        auto end = chrono::high_resolution_clock::now();

        // calculamos la duración
        // chrono::duration -> representa un intervalo de tiempo , definte <tipoDato, unidadTiempo>
        chrono::duration<double, milli> duration = end - start;
        cout << "La duración fue " << duration.count() << " ms " <<  endl;
        // Duración en segundos
        chrono::duration<double> duration_s = end - start;
        cout << "Duración en segundos: " << duration_s.count() << " s" << endl;
    }
        
}