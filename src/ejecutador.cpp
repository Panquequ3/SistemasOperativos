#include <iostream>
#include <vector>
#include <string>
#include <chrono> //para la medición del tiempo
#include <fstream>
#include "ejecutador.h"
using namespace std;
void writeArchive(string dataPath, int thread, double duration){
    ofstream resultArc(dataPath, ios::app);

    if(!resultArc){
        cerr << "Error, no se pudo abrir el archivo para escritura" << endl;
        return;
    }

    resultArc << to_string(thread) + ";" + to_string(duration) << endl;

    resultArc.close();
}

void ejecute(int thread, string cmd, int repeats, string dataPath){
    double duration;

    string command = "./paralelo " + to_string(thread) + " " + cmd;
    if(repeats >= 2){    
        for(int i = 0; i < repeats; i++){
            cout << "cantidad de hilos usados: " << thread << endl;

            // inicio de la medición
            auto start = chrono::high_resolution_clock::now();

            system(command.c_str());

            // para finalizar el tiempo de medición
            auto end = chrono::high_resolution_clock::now();

            // calculamos la duración
            // chrono::duration -> representa un intervalo de tiempo , definte <tipoDato, unidadTiempo>
            chrono::duration<double> dur = end - start;
            duration = dur.count();

            writeArchive(dataPath, thread, duration);
            cout << "La duración fue " << duration << " [s] " <<  endl;
        }
    }else{
        cout << "el numero de repeticiones debe ser mayor o igual que 2, vuelva a intentarlo" << endl;
    }
        
}