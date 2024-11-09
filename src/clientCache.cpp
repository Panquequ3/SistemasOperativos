#include <iostream>
#include <vector>
#include "cache.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include <laserpants/dotenv/dotenv.h>
#include <unordered_map>
#include <queue>
#include <unistd.h> 
#include <cstring> 
#include <sys/un.h>

using namespace std;
const string CLIENT_SOCKET_PATH = "./data/socket/socket_11"; 
const string SERVER_SOCKET_PATH = "./data/socket/socket_11_2";
const string mem_size = "MEMORY_SIZE";

atomic<bool> running(true);
// El servidor es el programa o proceso que espera las solicitudes de los 
// clientes. Su función principal es escuchar conexiones entrantes y procesar
// las solicitudes de los clientes. Una vez que recibe una solicitud, 
// el servidor realiza la acción correspondiente (por ejemplo, devolver
// información o procesar datos) y luego envía la respuesta al cliente.

// El cliente es el programa o proceso que inicia una conexión con el servidor. 
// Su tarea es ENVIAR SOLICITUDES al servidor y recibir respuestas. 
// En otras palabras, el cliente solicita un servicio o recurso del servidor.

void handleClient(int client_fd) {
    sockaddr_un address;
    char buffer[1048] = {0};

    // Crear el socket para el servidor final
    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        cerr << "Error al crear el socket del intermediario para el servidor final" << endl;
        close(client_fd);
        return;
    }

    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SERVER_SOCKET_PATH.c_str(), sizeof(address.sun_path) - 1);

    if (connect(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        cerr << "Error al conectar con el servidor final" << endl;
        close(client_fd);
        close(server_fd);
        return;
    }

    dotenv::init();
    string memo_size = dotenv::getenv(mem_size.c_str());
    int memory_size = atoi(memo_size);
    unordered_map<string, string> cache; // inicializamos el cache
    queue<string> cacheAux;

    while (running) {
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = read(client_fd, buffer, sizeof(buffer) - 1);

        if (bytesRead <= 0) {
            break;
        }

        cout << "Intermediario recibió del Cliente: " << buffer << endl;

        string message(buffer);

        if (strcmp(buffer, "SALIR AHORA") == 0) {
            send(server_fd, buffer, bytesRead, 0);
            running = false;
            break;
        }
        //aqui se comprueba que si no esta en memoria procesarlo
        if (searchOnCache(message)==-1) {
            // Enviar el mensaje al servidor final
            send(server_fd, buffer, bytesRead, 0);

            // Leer la respuesta del servidor final
            memset(buffer, 0, sizeof(buffer));
            bytesRead = read(server_fd, buffer, sizeof(buffer) - 1);
            if (bytesRead <= 0) {
                break;
            }

            cout << "Intermediario recibió del Servidor Final: " << buffer << endl;
            //aqui debe almacenarlo
            answer.assign(buffer); 
            writeCache(cacheAux, cache, answer, message, cacheSize);
            // Enviar la respuesta del servidor final al cliente
            send(client_fd, buffer, bytesRead, 0);
        } else {
            // Aqui busca la respuesta al mensaje
            // Enviar una respuesta directa al cliente
            string respuesta = cache.at(message);
            send(client_fd, respuesta.c_str(), respuesta.size(), 0);
        }
    }

    close(client_fd);
    close(server_fd);
}

void startIntermediaryServer() {
    int server_fd, client_fd;
    sockaddr_un address;

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        cerr << "Error al crear el socket del intermediario" << endl;
        return;
    }

    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, CLIENT_SOCKET_PATH.c_str(), sizeof(address.sun_path) - 1);

    unlink(CLIENT_SOCKET_PATH.c_str());
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        cerr << "Error en bind" << endl;
        close(server_fd);
        return;
    }

    if (listen(server_fd, 5) < 0) {
        cerr << "Error en listen" << endl;
        close(server_fd);
        return;
    }

    cout << "Intermediario iniciado en " << CLIENT_SOCKET_PATH << endl;

    // Aceptar conexiones del cliente
    while (running && (client_fd = accept(server_fd, nullptr, nullptr)) >= 0) {
        std::thread(handleClient, client_fd).detach();
    }

    close(server_fd);
    unlink(CLIENT_SOCKET_PATH.c_str());
}

int main(int argc, char* argv[]){
    startIntermediaryServer();
    return 0;
}