#include <iostream>  
#include <vector>
#include <string>
#include <map>
#include "cache.h"
#include <queue> // Para la cola de lineas
#include <unordered_map>
#include <sys/socket.h>

using namespace std;

void receiveMessages(int clientSocket) {
    char buffer[1024];
    ssize_t bytesRead;
    // obs: ssize_t recv(int sockfd, void *buf, size_t len, int flags);

    // mientras devuelva >0 sisgnifica que se han recibido datos y el
    // bucle procesara datos
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytesRead] = '\0';
        cout << buffer << endl;
    }
}


// Recibe "la solicitud", y busca en la cache o envia solicitud al motor de busqueda
// de ser necesario
// cache <message, answer>, cacheAux[message]
string cache(queue<string> cacheAux, unordered_map<string, string> cache, string message, int cacheSize){
    int search = searchOnCache(cache, message);
    string answer;
    // Si no la encuentra, se comunica con el motor de busqueda
    if (search == -1) {  
        string searchAnswer; // = -respuesta del motor de busqueda-
        answer = searchAnswer; 
        writeCache(cacheAux, cache, answer, message, cacheSize);
    } else{
        answer = cache.at(message);
    }
    return answer;
}

// Busca la palabra en cache, si la encuentra retorna 1, si no -1
int searchOnCache(unordered_map<string, string> cache, string message){
    auto result = cache.at(message);
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