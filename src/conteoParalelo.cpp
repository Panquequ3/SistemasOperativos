#include "conteoParalelo.h"
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

// VARIABLES GLOBALES
queue<filesystem::directory_entry> taskQueue; // Cola de tareas. Global para que todos los hilos tengan acceso a la misma instancia
mutex queueMutex; // Mutex para proteger la cola. Global para asegurar una buena sincronización
condition_variable condV; // Variable de condición. Global para simplificar implementación
bool finished = false;      // Variable para indicar si todas las tareas han sido procesadas. Global para simplificar implementación

// obs directory_entry: contiene información sobre un archivo o subdirectorio,
// por ejemplo, path, tipo de archivo.. etc

/**
 * @brief Función que toma palabras de un archivo y las almacena en un unordered_set
 * obs : solo es util para archivos que tienen una palabra por linea.
 * @param folderP path de la carpeta de los archivos a mapear
 * @param folderR path de la carpeta donde dejar el archivo map
 * @param extension extensión de los archivos a procesar y a almacenar en el archivo map
 */
unordered_set<string> archiveToSet(string wordsPath){
    ifstream archive(wordsPath);  // Abre el archivo para procesarlo
    // obs : archive = true -> si se abrió correctamente, sino, false
    if (!archive) { 
        cerr << "Error: No se pudo abrir el archivo " << wordsPath << endl;
        return {}; //retornamos un conjunto vacio
    }

    unordered_set<string>words;
    // obtiene la linea del archivo de entrada y la almacena en "line"
    string line;
    while (getline(archive, line)) { // Lee el archivo línea por línea
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v")); // limpiamos la linea (eliminamos espacios en blanco al principio y final)
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1); // el +1 asegura que limpiamos desde el 1er espacio blanco
        words.insert(line); // llenamos el set con las palabras del archivo
    }

    archive.close();
    return words;
}

/**
 * @brief Funcion que mapea los archivos a procesar en un archivo y una estructura, tipo map, con la forma: nombreArchivo, ID
 * 
 * @param folderP path de la carpeta de los archivos a mapear
 * @param folderR path de la carpeta donde dejar el archivo map
 * @param extension extensión de los archivos a procesar y a almacenar en el archivo map
 */
map<string, int> mapArchive(string folderP, string folderR, string extension){
    map<string, int> mapArc; // map con lo mismo que tendrá el archivo
    int id = 0;
    ofstream mapA(folderR + "/map.txt");  //Creamos el archivo

    // directory_iterator: Se usa para recorrer los archivos y subdirectorios de un directorio. 
    // Es un iterador que avanza de archivo en archivo. (iterador Lazy => no carga todos los archivos en memoria de una vez)
    // Al ser lazy, solo va iterando mientras se le indique, por ello es que
    // utilizamos un ciclo for  

    for (const auto& input : filesystem::directory_iterator(folderP)) {
        if (input.path().extension() == extension) {
            // escribimos el archivo con la forma de un hashmap
            mapA << input.path().stem() << ", " << id << endl;
            // añadimos tambien al map
            mapArc[input.path().stem()] = id;
            id++;
        }
    }
    mapA.close(); 
    return mapArc;
}

/**
 * @brief Funcion que limpia el archivo de entrada de las stopwords
 * 
 * @param stopWords set con las stopwords
 * @param archive path del archivo a procesar
 * @param pathTemp path de la carpeta donde se almacenaran archivos temporales a procesar
 */
void cleanArc(unordered_set<string> stopWords, string archive, string pathTemp){
    // abrimos archivo para lectura : 
    ifstream inputAr(archive); 
    string filePath = filesystem::path(archive).stem().string();

    if (!inputAr) { // Verifica si el archivo se abrió correctamente
        cerr << "No se pudo abrir el archivo para lectura." << endl;
        return;  
    }

    // abrimos archivo para escritura y posteriormente reescribirlo
    ofstream outputAr(pathTemp + "/" + filePath + "(p).txt");
    if (!outputAr) {
        cerr << "No se pudo abrir el archivo para escritura." << endl;
        return;  
    }

    //reescribiremos el archivo original sin las stopwords en uno nuevo
    string line;
    while (getline(inputAr, line)) { // Lee el archivo línea por línea
        istringstream stream(line); // Convierte la línea en un stream para procesar palabra por palabra
        string word;
        while (stream >> word) { // Extrae cada palabra de la línea
            // Si la palabra no es una stopword la escribimos
            transform(word.begin(), word.end(), word.begin(), ::tolower); //lo transformamos a minusculas para comparar
            if(stopWords.find(word) == stopWords.end()){
                outputAr << word << " ";
            }

        }
        //una vez terminan las palabras en la linea, seguimos con la siguiente
        outputAr << "\n"; 
    }

    inputAr.close(); 
    outputAr.close();
}

/**
 * @brief Funcion que procesa los archivos (los limpia de las stopwords y luego las procesa)
 * 
 * @param folderR path de la carpeta donde dejar los resultados
 * @param extension extension de los archivos a procesar
 * @param stopWords set con las stopwords a eliminar del archivo a procesar
 * @param fileMap Map de la forma : nombreArchivo, ID
 * @param tempPath Path de la carpeta donde almacenar archivos temporales
 */
void fileProcess(string folderR, string extension, unordered_set<string> stopWords, map<string, int> fileMap, string tempPath) {
    while (true) {        
            if (!taskQueue.empty()) {            
            unique_lock<mutex> lock(queueMutex); // Bloquea la cola
            map<string, int> wordCounter;

            // Verifica si la cola tiene tareas
            if (taskQueue.empty()) return;

            filesystem::directory_entry tarea = taskQueue.front(); // Toma la tarea del frente de la cola
            taskQueue.pop(); // Elimina la tarea de la cola
            lock.unlock(); // Liberar el mutex antes de procesar
            
            cleanArc(stopWords, tarea.path(), tempPath); //limpiamos el archivo

            string pathProcess = tempPath + "/" + tarea.path().stem().string() + "(p).txt"; //Path del archivo a procesar
            ifstream inputFile(pathProcess); // Abre el archivo para procesarlo

            if (!inputFile) { // Verifica si el archivo se abrió correctamente
                cerr << "No se pudo abrir el archivo para lectura." << endl;
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
            // Path donde se almacenará el archivo
            string resultPath = folderR + "/" + tarea.path().stem().string() + ".txt";

            cout << resultPath << ", " << wordCounter.size() << " palabras distintas" << endl;
            inputFile.close();

            //ahora escribiremos los resultados en un archivo creado en otra carpeta
            ofstream outputFile(resultPath);
                    
            if (!outputFile) {
                cerr << "No se pudo crear el archivo de salida." << endl;
            }

            for (const auto& par : wordCounter) {
                outputFile << par.first << "; " << par.second << endl;
            }
                    
            outputFile.close();
            wordCounter.clear();

            // (para verificar que los archivos hayan sido limpiados correctamente, comentar esta sección)
            // Eliminamos el archivo temporal creado
            if(remove(pathProcess.c_str()) != 0 )
                cout << "no se pudo eliminar el archivo temporal indicado " << endl;

        }else if (finished) {
            break; // Salir si no hay más tareas y se ha terminado
        }
    }
}

/**
 * @brief Funcion que asigna los hilos y les entrega tareas necesarias
 * 
 * @param numThreads numero de hilos a utilizar
 * @param folderP path del archivo a procesar
 * @param folderR path del archivo en donde dejar los resultados
 * @param extension extension de los archivos a procesar
 */
void assignThreads(int numThreads, string folderP, string folderR, string extension, string stopWordPath, string tempPath){
        if (folderP != folderR){
            extension = "." + extension;
            unordered_set<string> stopWords = archiveToSet(stopWordPath); //Creamos el set con las stopwords
            map<string, int> fileMap = mapArchive(folderP, folderR, extension); //creamos el archivo map, y de paso una estructura auxiliar

            thread threads[numThreads]; //Creamos los hilos a utilizar
                // Recorremos y imprimimos todos los elementos

            for (int i = 0; i < numThreads; ++i) {
                threads[i] = thread(fileProcess, folderR, extension, stopWords, fileMap, tempPath);
            } //quedan en espera hasta que hayan tareas en cola

            // Llenar la cola de tareas con los archivos que coincidan con la extensión
            //obs 1 : pasamos los valores por referencia, pero sin la posibilidad de 
            // modificarlos (const)
            //obs 2 : "auto" te permite declarar variables sin especificar explícitamente su tipo
            for (const auto& input : filesystem::directory_iterator(folderP)) {
                if (input.path().extension() == extension) {
                    // Protege las operaciones dentro de este bloque (evitamos que más de un hilo acceda)
                    lock_guard<mutex> lock(queueMutex); // asegura que la cola de tareas taskQueue esté protegida mientras se inserta una nueva tarea
                    taskQueue.push(input);
                }
                condV.notify_one(); // notificamos a un hilo
            }
            // A medida de que se llena la cola de tareas, tambien se le está entregando las tareas
            // a los hilos, si están todos ocupados, la nueva tarea se queda esperando a un hilo.

            // Marcar que todas las tareas han sido agregadas y finalizadas
            {
                lock_guard<mutex> lock(queueMutex); // se usa en este caso para proteger la operación de escritura en la variable
                finished = true;
            } // obs : está entre llaves para delimitar el scope, una vez salga del bloque, se "desbloquea"
            condV.notify_all(); // Notificar a todos los hilos para que salgan

            // Esperar a que todos los hilos terminen
            for (auto& th : threads) {
                th.join();
            }
    } else {
        cout << "ERROR : La carpeta de entrada y de salida son las mismas, porfavor ingrese direcciones diferentes" << endl;
    }

}