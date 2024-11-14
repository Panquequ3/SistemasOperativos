#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <map>
#include <vector>
#include <laserpants/dotenv/dotenv.h>
#include "motorBusqueda.h"

using namespace std;

const string index_p = "INDEX_PATH";
const string top = "TOPK";
const int PORT = 8081; // Puerto en el que el servidor escuchará las conexiones

void startFinalServer() {
    int server_fd, client_fd;
    sockaddr_in address;
    char buffer[1048] = {0};
    int opt = 1;
    int addrlen = sizeof(address);

    // Crear el socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Error al crear el socket del servidor final");
        exit(EXIT_FAILURE);
    }

    // Opción para reutilizar la dirección y puerto
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Error en setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Vincular el socket a la dirección y puerto
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

    cout << "Servidor final iniciado en el puerto " << PORT << endl;

    // Aceptar la conexión del cliente
    client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (client_fd < 0) {
        perror("Error al aceptar conexión");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    dotenv::init();
    string index_path = dotenv::getenv(index_p.c_str());
    int topk = atoi(dotenv::getenv(top.c_str()).c_str());
    map<string, vector<string>> index = getIndex(index_path);
    string message;
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytesRead <= 0) {
            break;
        }

        cout << "Servidor final recibió: " << buffer << endl;

        // Salir si el mensaje es "SALIR AHORA"
        if (strcmp(buffer, "SALIR AHORA") == 0) {
            cout << "Servidor final cerrando conexión" << endl;
            break;
        }
        message.assign(buffer);
        string response = getWords(index, message, topk);
        send(client_fd, response.c_str(), response.size(), 0);
    }

    close(client_fd);
    close(server_fd);
}

int main() {
    startFinalServer();
    return 0;
}
