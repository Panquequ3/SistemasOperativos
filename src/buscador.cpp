#include <iostream>  
#include <vector>
using namespace std;

void searcher(string outputWord = "SALIR AHORA"){
    string inputPhrase;
    cout << "+---------------------------+ " << endl;
    cout << "| ¡Bienvenido al buscador!  |" << endl;
    cout << "+---------------------------+ " << endl;
    cout << "(Si desea salir, escriba: '" << outputWord << "')" << endl;
    cout <<  "\ningrese la frase a buscar: ";
    cin >> inputPhrase;

    if(inputPhrase == outputWord)
        cout << "¡¡Hasta pronto!!" << endl;
    else{//llamamos al cache y al motor de busqueda

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

}