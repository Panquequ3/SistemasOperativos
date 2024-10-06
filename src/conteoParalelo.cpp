#include <iostream>
#include <fstream>
#include <string>
#include <map> //para map, para almacenar cada palabra y su cantidad de apariciones en un archivo
#include <sstream> // Para istringstream
#include <filesystem> //para explorar archivos en una carpeta
#include "wordCounter.h"
#include <thread>

using namespace std;

void cleanArc(string stopWord, string folderP, thread hilo){

}

void fileProcess(const auto& inPath, string folderR, string extension) {
    extension = "." + extension;
    map<string, int> wordCounter;

    // Itera a través de todos los archivos con en la carpeta indicada a procesar
    //obs: "auto" te permite declarar variables sin especificar explícitamente su tipo
        if (inPath.extension() == extension) {
            //cout << "Nombre del archivo: " << input.path().filename() << endl;

            ifstream inputFile(inPath);  // Abre el archivo para procesarlo

            if (!inputFile) { // Verifica si el archivo se abrió correctamente
                cerr << "No se pudo abrir el archivo para lectura." << endl;
                continue; //instrucción de control de flujo en los bucles que sirve para saltarse el resto del código dentro del 
                        //bucle para la iteración actual y pasar inmediatamente a la siguiente iteración.
            }
            string line;
            while (getline(inputFile, line)) { // Lee el archivo línea por línea
                istringstream stream(line); // Convierte la línea en un stream para procesar palabra por palabra
                string palabra;
                while (stream >> palabra) { // Extrae cada palabra de la línea
                    wordCounter[palabra]++; // Incrementa el contador para la palabra en el map
                    // Si la palabra es nueva, se crea en el map con valor 1
                    // Si ya existe, se incrementa su contador
                }
            }
            cout << inPath << ", " << wordCounter.size() << " palabras distintas" << endl;
            inputFile.close();

            //ahora escribiremos los resultados en un archivo creado en otra carpeta
            ofstream outputFile(folderR + "/" + inPath.stem().string()+".txt");
            
            if (!outputFile) {
                cerr << "No se pudo crear el archivo de salida." << endl;
                continue;
            }

            for (const auto& par : wordCounter) {
                outputFile << par.first << "; " << par.second << endl;
            }
            
            outputFile.close();
            wordCounter.clear();
        }

}

void assignThreads(int threads, string folderP, string folderR, string extension){
    vector<thread> hilos;

    // Itera a través de todos los archivos con en la carpeta indicada a procesar
    //obs: "auto" te permite declarar variables sin especificar explícitamente su tipo

    for (const auto& input : filesystem::directory_iterator(folderP)) {
        if (input.path().extension() == extension) {
            //cout << "Nombre del archivo: " << input.path().filename() << endl;

            ifstream inputFile(input.path());  // Abre el archivo para procesarlo

            if (!inputFile) { // Verifica si el archivo se abrió correctamente
                cerr << "No se pudo abrir el archivo para lectura." << endl;
                continue; //instrucción de control de flujo en los bucles que sirve para saltarse el resto del código dentro del 
                        //bucle para la iteración actual y pasar inmediatamente a la siguiente iteración.
            }
            string line;
            while (getline(inputFile, line)) { // Lee el archivo línea por línea
                istringstream stream(line); // Convierte la línea en un stream para procesar palabra por palabra
                string palabra;
                while (stream >> palabra) { // Extrae cada palabra de la línea
                    wordCounter[palabra]++; // Incrementa el contador para la palabra en el map
                    // Si la palabra es nueva, se crea en el map con valor 1
                    // Si ya existe, se incrementa su contador
                }
            }
            cout << input.path() << ", " << wordCounter.size() << " palabras distintas" << endl;
            inputFile.close();

            //ahora escribiremos los resultados en un archivo creado en otra carpeta
            ofstream outputFile(folderR + "/" + input.path().stem().string()+".txt");
            
            if (!outputFile) {
                cerr << "No se pudo crear el archivo de salida." << endl;
                continue;
            }

            for (const auto& par : wordCounter) {
                outputFile << par.first << "; " << par.second << endl;
            }
            
            outputFile.close();
            wordCounter.clear();
        }
    } 
}