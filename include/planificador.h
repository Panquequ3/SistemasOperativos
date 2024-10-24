#include <iostream>  
#include <vector> // Para vector
#include <fstream> // Para escribir, leer archivos, etc
#include <filesystem> //para explorar archivos en una carpeta
using namespace std;

int findDisp(int numCore, vector<bool> list, string path );
void archiveCores(int numCores, string path );
void cleanAC(string path );
void coordinator(int numCores, string tasksPath, string corePath, string resultPath);