#include <iostream>  
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;
// Busca la palabra en cache, si la encuentra retorna el indice, si no -1
int searchOnCache(unordered_map<string, string> cache, string message);

// Escribe los resultados en la cache, si esta está llena entonces elimina la
// busqueda más antigua y añade la nueva
void writeCache(queue<string>& cacheAux, unordered_map<string, string>& cache, string answer, string message, int cacheSize);