#include <iostream>  
#include <vector>
#include <string>
#include "cache.h"
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

// Encuentra el indice del primer simbolo que encuentre en el str
int findIndex(string str, char simb){
    int i = 0;
    for(char car : str){
        if(car == simb)
            return i 
        i++;
    }
}

// Recibe "la solicitud", y busca en la cache o envia solicitud al motor de busqueda
// de ser necesario
string cache(vector<string> cache, string lineToIn, int cacheSize){

    int search = searchOnCache(cache, lineToIn, actualSize);
    string answer;
    // Si no la encuentra, se comunica con el motor de busqueda
    if (search == -1) {  
        string searchAnswer; // = -respuesta del motor de busqueda-
        writeCache(cache, lineToIn, searchAnswer);
        answer = searchAnswer;
    } else{
        answer = cache[search];
    }
    return answer;
}

// Busca la palabra en cache, si la encuentra retorna el indice, si no -1
int searchOnCache(vector<string> cache, string lineToIn, int size){
    for(int i = 0; i < size; i++){
        int index = findIndex(cache[i], ';');
        string line = cache[i].substr(0, i);
        if(lineToIn == line)
            return i;
    }
    cout << "frase no encontrada, enviar solicitud a motor de busqueda" << endl;
    return -1;
}

// Escribe los resultados en la cache, si esta está llena entonces elimina la
// busqueda más antigua y añade la nueva
void writeCache(vector<string> cache, string searchAnswer, int cacheSize){
    int actualSize = cache.size(); // Cuan llena está la cache actualmente
    
    if (cacheSize == actualSize) {
        cache.erase(cache.begin());  // Elimina la busqueda más antigua
        cache.push_back(searchAnswer); // Añade la busqueda mas reciente
    } else{
        cache.push_back(searchAnswer); // Añade la busqueda mas reciente
    }

}