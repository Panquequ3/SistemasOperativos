#include <iostream>
#include <fstream>
#include <string>
#include <map> //para map, para almacenar cada palabra y su cantidad de apariciones en un archivo
#include <sstream> // Para istringstream
#include <filesystem> //para explorar archivos en una carpeta
#include "contadorPalabras.h"
using namespace std;

void procesa(string carpetaP, string carpetaR, string extension) {
    extension = "." + extension;
    map<string, int> contadorPalabras;
    // Itera a través de todos los archivos con en la carpeta indicada a procesar
    //obs: "auto" te permite declarar variables sin especificar explícitamente su tipo
    for (const auto& entrada : filesystem::directory_iterator(carpetaP)) {
        if (entrada.path().extension() == extension) {
            cout << "Nombre del archivo: " << entrada.path().filename() << endl;

            ifstream archivoEntrada(entrada.path());  // Abre el archivo para procesarlo

            if (!archivoEntrada) { // Verifica si el archivo se abrió correctamente
                cerr << "No se pudo abrir el archivo para lectura." << endl;
                continue; //instrucción de control de flujo en los bucles que sirve para saltarse el resto del código dentro del 
                        //bucle para la iteración actual y pasar inmediatamente a la siguiente iteración.
            }
            string linea;
            while (getline(archivoEntrada, linea)) { // Lee el archivo línea por línea
                istringstream stream(linea); // Convierte la línea en un stream para procesar palabra por palabra
                string palabra;
                while (stream >> palabra) { // Extrae cada palabra de la línea
                    contadorPalabras[palabra]++; // Incrementa el contador para la palabra en el map
                    // Si la palabra es nueva, se crea en el map con valor 1
                    // Si ya existe, se incrementa su contador
                }
            }
            cout << entrada.path().filename() << ", " << contadorPalabras.size() << " palabras distintas" << endl;
            archivoEntrada.close();

            //ahora escribiremos los resultados en un archivo creado en otra carpeta
            ofstream archivoSalida(carpetaR + "/" + entrada.path().stem().string() + "Re" + extension);
            
            if (!archivoSalida) {
                cerr << "No se pudo crear el archivo de salida." << endl;
                continue;
            }

            for (const auto& par : contadorPalabras) {
                archivoSalida << par.first << "; " << par.second << endl;
            }
            
            archivoSalida.close();
            contadorPalabras.clear();
        }
    } 
}