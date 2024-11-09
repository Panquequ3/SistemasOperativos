#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <map>
#include <vector>
#include <laserpants/dotenv/dotenv.h>
#include "motorBusqueda.h"

using namespace std;

const string index_p = "INDEX_PATH";
const string top = "TOPK";
const string SOCKET_PATH = "./data/socket/socket_11_2";

void startFinalServer() {
    int server_fd, client_fd;
    sockaddr_un address;
    char buffer[1048] = {0};

    // Crear el socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        cerr << "Error al crear el socket del servidor final" << endl;
        return;
    }

    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCKET_PATH.c_str(), sizeof(address.sun_path) - 1);

    unlink(SOCKET_PATH.c_str());
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

    cout << "Servidor final iniciado en " << SOCKET_PATH << endl;

    // Aceptar la conexión del cliente
    client_fd = accept(server_fd, nullptr, nullptr);
    if (client_fd < 0) {
        cerr << "Error al aceptar conexión" << endl;
        close(server_fd);
        return;
    }

    dotenv::init();
    string index_path = dotenv::getenv(index_p.c_str());
    int topk = atoi(dotenv::getenv(top.c_str()).c_str());
    map<string,vector<string>> index = getIndex(index_path);
    string message;
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytesRead <= 0) {
            break;
        }

        cout << "Servidor final recibió: " << buffer << endl;

        // Salir si el mensaje es "SALIR_AHORA"
        if (strcmp(buffer, "SALIR_AHORA") == 0) {
            cout << "Servidor final cerrando conexión" << endl;
            break;
        }
        message.assign(buffer);
        string response = getCoincidence(index,message,topk);
        write(client_fd, response.c_str(), response.size());
    }

    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH.c_str());
}

int main(){
    startFinalServer();
    return 0;
}