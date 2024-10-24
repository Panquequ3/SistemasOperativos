#include <iostream>  
#include <vector> // Para vector
#include <fstream> // Para escribir, leer archivos, etc
#include <filesystem> //para explorar archivos en una carpeta
#include "planificador.h"
using namespace std;

//Funcion que retorna:
// -1 : si no se encontro un core disponible
// indice : si encontró un core disponible 
// retorna el primer core encontrado
// 1: disp 0: ocupado 
int findDisp(int numCore, vector<bool> list, string path = "/temporal"){
    for (const auto& input : filesystem::directory_iterator(path)) {
        ifstream inputArc(input.path());
        if(!inputArc){
            cerr << "No se pudo abrir el archivo " << input.path().string() << " para lectura" << endl;
            continue; // Continúa al siguiente archivo
        }
        char state;

        if (inputArc.get(state)) { // Verifica si la lectura del primer caracter fue exitosa
            if (state == '1') {// Si está disponible entonces
                string i = input.path().stem().string();
                return stoi(i);
            }else
                inputArc.close(); //si no, seguimos
        } else {
            cerr << "No se pudo leer el estado del core" << input.path().stem().string() << endl;
        }  
    }
    // si no hay ninguno disponible entonces devolvemos -1
    return -1;
}


// funcion que crea los archivos para los cores
void archiveCores(int numCores, string path = "/temporal"){
    for(int i = 0; i < numCores; i++){
        ofstream outputArc(path + "/" + to_string(i) + ".txt");
        if (!outputArc) {
            cerr << "No se pudo abrir el archivo para escritura." << endl;
            return;  
        }
        outputArc << "1" << endl; // inicialmente todos en estado dispobible
        outputArc.close();
    }
}

void cleanAC(string path = "/temporal"){
    for (const auto& input : filesystem::directory_iterator(path)) {

        if(remove(input.path().c_str()) != 0 )
            cout << "no se pudo eliminar el archivo " << input.path().string() << " temporal indicado " << endl;

    }
}
//corePath recibira temp
void coordinator(int numCores, string tasksPath, string corePath, string resultPath){
    // creamos los cores
    ofstream archiveCores(numCores, corePath); // creamos los archivos de estado de los cores

    // procesamos el archivo con las tareas ---------------------------------------------------------
    vector<string> listTask; // creamos la lista de tareas (las operaciones)

    ifstream taskArchive(tasksPath); //Abrimos el archivo de con las operaciones

    if(!taskArchive){
        cerr << "Error, no se pudo abrir el archivo, revise el path ingresado e intentelo nuevamente" << endl;
        return;
    }
    // añadimos las tareas en un formato util
    string line;
    while(getline(archiveCores, line)){
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v")); // limpiamos la linea (eliminamos espacios en blanco al principio y final)
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1); // el +1 asegura que limpiamos desde el 1er espacio blanco
        listTask.push_back(line);
    }
    taskArchive.close();

    // ----------------------------------------------------------------------------------------------

    // asignamos las tareas a los diferentes cores
    int completedTask = 0, totalTask = listTask.size(), i = 0, core;

    while (completedTask < totalTask){
        string t = listTask[i]; // tomamos una tarea
        core = findDisp(numCores, corePath); // tomamos un core que la ejecute
        if (core != -1){ // si hay uno disponible, le otorgamos la tarea

        // --------------------- Cambiamos su estado ------------------------------
            ifstream coreArc(corePath + "/" + to_string(core) + ".txt");
            if(!coreArc){
                cerr << "Error, no se pudo abrir el archivo, revise el path ingresado e intentelo nuevamente" << endl;
            }
            coreArc.seekp(0); // Mover el puntero de escritura al inicio del archivo
            coreArc.put('1'); // Cambiamos su estado a ocupado
            coreArc.close();
        // ------------------------------------------------------------------------
            string msg = "(" + core + ":" + t + ")";
            string command = "./dist " +  msg  + " " + resultPath " " + corePath;
            system(command.c_str());
            i++; //marcamos la tarea completada
        } // si no, seguimos esperando un core disponible
    }

}