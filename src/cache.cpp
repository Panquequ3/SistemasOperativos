#include <iostream>  
#include <vector>
#include <string>
#include <map>
#include "cache.h"
#include <queue> // Para la cola de lineas
#include <unordered_map>
#include <sys/socket.h>

using namespace std;

// Busca la palabra en cache, si la encuentra retorna 1, si no -1
int searchOnCache(const unordered_map<string, string>& cache, const string& message) {
    auto result = cache.find(message);
    if (result != cache.end()) {
        return 1; // frase encontrada
    } else {
        return -1; // frase no encontrada
    }
}


// Escribe los resultados en la cache, si esta está llena entonces elimina la
// busqueda más antigua y añade la nueva
void writeCache(queue<string>& cacheAux, unordered_map<string, string>& cache, string answer, string message, int cacheSize){
    int actualSize = cache.size(); // Cuan llena está la cache actualmente
    string lastSearch; // Para almacenar busqueda más vieja

    // Si el caché está lleno entonces eliminamos el mas viejo
    if (cacheSize == actualSize) {
        lastSearch = cacheAux.front(); // Guardamos la busqueda más vieja para más tarde

        cacheAux.pop(); // Elimina la busqueda más antigua del auxiliar
        cache.erase(lastSearch); // Elimina la busqueda más antigua en el caché

        cacheAux.push(message); // Añade la busqueda mas reciente al auxiliar
        cache[message] = answer; // Añade la busqueda mas reciente al caché
    } else{ // si no, añadimos la busqueda mas reciente
        cacheAux.push(message); 
        cache[message] = answer;
    }
}