#include <iostream>
#include <fstream> // Para escribir, leer archivos, etc
#include <string>
#include <map> // Para map, para almacenar cada palabra y su cantidad de apariciones en un archivo
#include <sstream> // Para istringstream
#include <filesystem> //para explorar archivos en una carpeta
#include <queue> // Para la cola de procesos
#include <thread> // Para los hilos
#include <mutex> // Un mutex es un mecanismo de sincronización que asegura que solo un hilo pueda acceder a una sección crítica del código al mismo tiempo.
#include <condition_variable> // Proporciona una forma de manejar la sincronización entre hilos
#include <unordered_set> // Estructura de datos que almacena elementos unicos
#include <cstdio>  // Para remove() y rename()
#include <algorithm> // Para transform

using namespace std;

unordered_set<string> archiveToSet(string wordsPath);
map<string, int> mapArchive(string folderP, string folderR, string extension);
void cleanArc(unordered_set<string> stopWords, string archive, string pathTemp);
void fileProcess(string folderR, string extension, unordered_set<string> stopWords, map<string, int> fileMap, string tempPath);
void assignThreads(int numThreads, string folderP, string folderR, string extension, string stopWordPath, string tempPath);