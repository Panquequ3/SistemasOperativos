#include <iostream>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include "motorBusqueda.h"
#include "buscador.h"

using namespace std;

const int INTERMEDIARY_PORT = 8080; // Puerto del intermediario
const string INTERMEDIARY_IP = "127.0.0.1"; // Dirección IP del intermediario

void startClient(string map_path, string outputWord = "SALIR AHORA") {
    int client_fd;
    sockaddr_in address;
    char buffer[1048] = {0};

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        cerr << "Error al crear el socket del cliente" << endl;
        return;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(INTERMEDIARY_PORT);
    address.sin_addr.s_addr = inet_addr(INTERMEDIARY_IP.c_str());

    if (connect(client_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        cerr << "Error al conectar con el intermediario" << endl;
        close(client_fd);
        return;
    }

    string message;
    cout << "+---------------------------+ " << endl;
    cout << "| ¡Bienvenido al buscador!  |" << endl;
    cout << "+---------------------------+ " << endl;
    cout << "(Si desea salir, escriba: '" << outputWord << "')" << endl;

    while(true){
        cout <<  "\ningrese la frase a buscar: ";
        cin >> message;

        if(message == outputWord){
            cout << "¡¡Hasta pronto!!" << endl;
            send(client_fd, outputWord.c_str(), message.size(), 0);
            break;
        }

        send(client_fd, message.c_str(), message.size(), 0);

        memset(buffer, 0, sizeof(buffer));
        int bytesRead = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            cout << "Cliente recibió del Intermediario: " << buffer << endl;
            string answer;
            answer.assign(buffer); // respuesta que recibe del cache
            vector<string> results = translateA(answer, map_path);
            printResults(results);
        }
    }

    close(client_fd);
}

void printResults(vector<string> vec) {
    for (string str : vec) {
        cout << str << endl;
    }
}

vector<string> split(string str){
    str = str + ';';
    int tam = str.size();
    vector<string> valores;
    string aux = "";
    for (int i = 0; i < tam; i++){
        if(str[i] != ';'){
            aux += str[i];
        } else{
            valores.push_back(aux);
            aux = "";
        }
    }
    return valores;
}

string searchOnMap(string mapPath, string id) {
    ifstream archive(mapPath);
    if (!archive) {
        cerr << "No se pudo abrir el archivo map" << endl;
        return "";
    }
    string line, name, idBook;
    while (getline(archive, line)) {
        if (!line.empty()) {
            size_t start = line.find('"');
            if (start != string::npos) {
                size_t end = line.find('"', start + 1);
                if (end != string::npos) {
                    name = line.substr(start + 1, end - 1);
                    idBook = line.substr(end + 2);
                    if (idBook == id) {
                        archive.close();
                        return name;
                    }
                }
            }
        }
    }
    archive.close();
    return "";
}

vector<string> translateA(string answer, string mapPath){
    vector<string> results;
    int score, position = 1;
    string book, id;
    vector<string> searchResults = split(answer);
    for(string elem : searchResults){
        id = extractId(elem).substr(2);
        score = extractCant(elem);
        book = searchOnMap(mapPath, id);
        results.push_back(to_string(position) + ") " + "("+ to_string(score) + ") " + book );
        position++;
    }
    return results;
}

int main(int argc, char* argv[]){
    if(argc != 2){
        cout << "Error. Debe ejecutarse como ./buscador mapPath" << endl;
        exit(EXIT_FAILURE);
    }
    string map_path = argv[1];
    startClient(map_path);
    return 0;
}
