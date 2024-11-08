#include <iostream>  
#include <vector>
#include <string>

using namespace std;

void receiveMessages(int clientSocket);

// Encuentra el indice del primer simbolo que encuentre en el str
int findIndex(string str, char simb);

// Recibe la solicitud, y busca en la cache o envia solicitud al motor de busqueda
// de ser necesario
string cache(vector<string> cache, string lineToIn, int cacheSize);

// Busca la palabra en cache, si la encuentra retorna el indice, si no -1
int searchOnCache(vector<string> cache, string lineToIn, int size);

// Escribe los resultados en la cache, si esta está llena entonces elimina la
// busqueda más antigua y añade la nueva
void writeCache(vector<string> cache, string searchAnswer, int cacheSize);