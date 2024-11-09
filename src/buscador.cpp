#include <iostream> 
#include <string> 
#include <vector>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include "motorBusqueda.h"
#include "buscador.h"


using namespace std;

const string INTERMEDIARY_SOCKET_PATH = "./data/socket/socket_11";

void startClient(string map_path, string outputWord = "SALIR AHORA") {
    int client_fd;
    sockaddr_un address;
    char buffer[1048] = {0};

    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd < 0) {
        cerr << "Error al crear el socket del cliente" << endl;
        return;
    }

    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, INTERMEDIARY_SOCKET_PATH.c_str(), sizeof(address.sun_path) - 1);

    if (connect(client_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        cerr << "Error al conectar con el intermediario" << endl;
        close(client_fd);
        return;
    }
    
    //aqui va la definicion de cosas dentro de la interfaz si llegase a ser necesario

    string message;

    //aqui se imprime el mensaje de la interfaz (parte visual)
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

        // Enviar mensaje al intermediario (AKA cache)
        send(client_fd, message.c_str(), message.size(), 0);

        // Leer la respuesta del intermediario
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            cout << "Cliente recibió del Intermediario: " << buffer << endl;
            string answer;
            answer.assign(buffer); // respuesta que recibe del cache
            vector<string> results =translateA(answer, map_path);
            printResults(results);
        }

    }

    close(client_fd);
}


// imprime los resultados del vector
void printResults(vector<string> vec) {
    for (string str : vec) {
        cout << str << endl;
    }
}

// separa un string por el caracter ";"
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
// busca los datos necesarios para imprimir la respuesta
string searchOnMap(string mapPath, string id) {
    ifstream archive(mapPath);  // Abre el archivo para procesarlo (lo abre modo lectura)

    if (!archive) { // Verifica si el archivo se abrió correctamente
        cerr << "No se pudo abrir el archivo map" << endl;
        return "";
    }

    string line, name, idBook;

    while (getline(archive, line)) { // Lee el archivo línea por línea 
        if (!line.empty()) {
            size_t start = line.find('"'); // en realidad siempre es 0
            if (start != string::npos) {
                // Encontrar la segunda aparición del símbolo
                size_t end = line.find('"', start + 1);
                if (end != string::npos) {
                    name = line.substr(start + 1, end - 1);
                    idBook = line.substr(end + 2); // +2 para saltar la comilla y la coma
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

// Traduce la respuesta y los guarda en un vector
vector<string>translateA(string answer, string mapPath){
    vector<string>results;
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
    // Deberiamos asegurar que se ejecuto la opcion que crea el mapa_Archivos??

