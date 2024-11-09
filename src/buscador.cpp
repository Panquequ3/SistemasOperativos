#include <iostream> 
#include <string> 
#include <vector>
#include "motorBusqueda.h"
#include <laserpants/dotenv/dotenv.h>

using namespace std;

const string map_path = "MAP_PATH";


// imprime el menu y espera la frase
void searcher(string outputWord = "SALIR AHORA"){
    string inputPhrase;
    cout << "+---------------------------+ " << endl;
    cout << "| ¡Bienvenido al buscador!  |" << endl;
    cout << "+---------------------------+ " << endl;
    cout << "(Si desea salir, escriba: '" << outputWord << "')" << endl;

    while(inputPhrase != outputWord){
        cout <<  "\ningrese la frase a buscar: ";
        cin >> inputPhrase;
        //llamamos al cache y al motor de busqueda
        string answer = ""; // respuesta que recibe del cache
        vector<string> = translate(answer, map_path);
    }
    if(inputPhrase == outputWord)
        cout << "¡¡Hasta pronto!!" << endl;


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
            valores.push_back(valor);
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
vector<string> translate(string answer, string mapPath){
    vector<string>results;
    int score, position = 1;
    string book, id;
    vector<string> searchResults = split(answer);
    for(string elem : searchResults){
        id = extractId(elem).substr(2);
        score = extractCant(elem);
        book = searchOnMap(mapPath, id);
        results.push_back(to_string(position) + ") " + "("+ score + ") " + book );
        position++;
    }
    return results;
}

int main(int argc, char* argv[]){
	// if(argc != n){
	// 	cout << "Error. Debe ejecutarse como ./buscador " << endl;
	// 	exit(EXIT_FAILURE);
	// }

    // buscador probablemente deba ser un cliente.. o utilizar colas de archivos
    return 0;
}
    // Deberiamos asegurar que se ejecuto la opcion que crea el mapa_Archivos??

