#include <iostream>
#include <vector>
#include "cache.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
using namespace std;

// El servidor es el programa o proceso que espera las solicitudes de los 
// clientes. Su función principal es escuchar conexiones entrantes y procesar
// las solicitudes de los clientes. Una vez que recibe una solicitud, 
// el servidor realiza la acción correspondiente (por ejemplo, devolver
// información o procesar datos) y luego envía la respuesta al cliente.

// El cliente es el programa o proceso que inicia una conexión con el servidor. 
// Su tarea es ENVIAR SOLICITUDES al servidor y recibir respuestas. 
// En otras palabras, el cliente solicita un servicio o recurso del servidor.


int main(int argc, char* argv[]){

    // Crear un socket del cliente
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (clientSocket == -1) {
        cerr << "Error al crear el socket del cliente" << endl;
        return -1;
    }   
    // Configurar la dirección del servidor
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_UNIX;
    serverAddr.sin_port = htons(12345); // Puerto del servidor
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección IP del servidor

    // Conectar al servidor
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error al conectar al servidor");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    cout << "Conectado al servidor." << endl;

    // Crear un nuevo hilo para recibir mensajes del servidor
    thread(receiveMessages, clientSocket).detach();

    string example = "hola mundo"; // Ejemplo de busqueda
    vector<string> cache; // inicializamos el cache
    // Enviar mensajes al servidor
    char message[1024];
    while (cin.getline(message, sizeof(message))) {
        string request ;
        // envia datos a través de un socket en una conexion de red
        send(clientSocket, fullMessage.c_str(), fullMessage.length(), 0);
    }

    // Cerrar el socket del cliente
    close(clientSocket);

    return 0;
}