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
#include <atomic>

using namespace std;

const int INTERMEDIARY_PORT = 8080; // Puerto para el intermediario que los clientes utilizarán
const int SERVER_PORT = 8081; // Puerto para el servidor final
const string mem_size = "MEMORY_SIZE";

atomic<bool> running(true);

void handleClient(int client_fd) {
    sockaddr_in server_address;
    char buffer[1048] = {0};

    // Crear el socket para el servidor final
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        cerr << "Error al crear el socket del intermediario para el servidor final" << endl;
        close(client_fd);
        return;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección del servidor final
    server_address.sin_port = htons(SERVER_PORT);

    if (connect(server_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Error al conectar con el servidor final");
        close(client_fd);
        close(server_fd);
        return;
    }

    dotenv::init();
    int memory_size = atoi(dotenv::getenv(mem_size.c_str()).c_str());
    unordered_map<string, string> cache; // Inicializamos el caché
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
        // Aquí se comprueba que si no está en memoria procesarlo
        string answer;
        if (searchOnCache(cache, message) == -1) {
            // Enviar el mensaje al servidor final
            send(server_fd, buffer, bytesRead, 0);

            // Leer la respuesta del servidor final
            memset(buffer, 0, sizeof(buffer));
            bytesRead = read(server_fd, buffer, sizeof(buffer) - 1);
            if (bytesRead <= 0) {
                break;
            }

            cout << "Intermediario recibió del Servidor Final: " << buffer << endl;
            // Aquí debe almacenarlo
            answer.assign(buffer);
            writeCache(cacheAux, cache, answer, message, memory_size);
            // Enviar la respuesta del servidor final al cliente
            send(client_fd, buffer, bytesRead, 0);
        } else {
            // Aquí busca la respuesta al mensaje
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
    sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Error al crear el socket del intermediario");
        exit(EXIT_FAILURE);
    }

    // Opción para reutilizar la dirección y puerto
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Error en setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección del intermediario
    address.sin_port = htons(INTERMEDIARY_PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Error en bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) {
        perror("Error en listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    cout << "Intermediario iniciado en el puerto " << INTERMEDIARY_PORT << endl;

    // Aceptar conexiones del cliente
    while (running && (client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) >= 0) {
        std::thread(handleClient, client_fd).detach();
    }

    close(server_fd);
}

int main(int argc, char* argv[]) {
    startIntermediaryServer();
    return 0;
}
