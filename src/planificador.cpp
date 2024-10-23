#include <iostream>  
#include <vector> // Para vector
#include <fstream> // Para escribir, leer archivos, etc
#include <filesystem> //para explorar archivos en una carpeta

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
        }
        char state;
        inputArc.get(state);

        //si está disponible entonces
        if(state == '1'){
            string i = input.path().stem().string();
            return stoi(i);
        } //si no, seguimos
        inputArc.close();
    }
    return -1;
}


//Funcion que pasa los elementos de un string de la forma 
// id;operación; num1, num2 a un vector -> {id, operacion, num1, num2}
void archiveCores(int numCores, string path = "/temporal"){
    for(int i = 0; i < numCores; i++){
        ofstream outputArc(path + "/" + to_string(i));
        if (!outputArc) {
            cerr << "No se pudo abrir el archivo para escritura." << endl;
            return;  
        }
        outputArc << "1" << endl;
        outputArc.close();
    }
}
void cleanAC(string path = "/temporal"){
    for (const auto& input : filesystem::directory_iterator(path)) {

        if(remove(input.path().c_str()) != 0 )
            cout << "no se pudo eliminar el archivo " << input.path().string() << " temporal indicado " << endl;

    }
}
void coordinator(int numCores, string tasksPath, string path){
    // creamos los cores
    // vector<bool> listCores;
    // creamos la lista de tareas (las operaciones)
    archiveCores(numCores); // creamos los archivos de estado de los cores
    // for(int i = 0; i < numCores; i++){
    //     listCores = true; //creamos la lista de cores, en estado disponible
    // }
    vector<string> listTask; // vector con las tareas
    // procesamos el archivo con las tareas

    ifstream taskArchive(tasksPath); //Abrimos el archivo de con las operaciones

    if(!taskArchive){
        cerr << "Error, no se pudo abrir el archivo, revise el path ingresado e intentelo nuevamente" << endl;
        return;
    }
    // añadimos las tareas en un formato util
    string line;
    while(getline(archive, line)){
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v")); // limpiamos la linea (eliminamos espacios en blanco al principio y final)
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1); // el +1 asegura que limpiamos desde el 1er espacio blanco
        listTask.push_back(line);
    }
    taskArchive.close();

    // asignamos las tareas a los diferentes cores
    int completedTask = 0, totalTask = listTask.size(), i = 0, core;

    while (completedTask < totalTask){
        string t = listTask[i];
        core = findDisp(numCores);
        if (core != -1){
            ifstream coreArc(path + "/" + to_string(core));
            if(!coreArc){
                cerr << "Error, no se pudo abrir el archivo, revise el path ingresado e intentelo nuevamente" << endl;
            }
            coreArc.seekp(0); // Mover el puntero de escritura al inicio del archivo
            coreArc.put('1'); // Aquí escribimos '1', reemplazando lo que había
            coreArc.close();
            
            string msg = "(" + core + ":" + t + ")";
            system(./mainDist msg);
            //proandoooo
        }
    }

}