#include <iostream>
#include <map>
// #include <sstream> // Para istringstream
// #include <filesystem> //para explorar archivos en una carpeta

using namespace std;

map<string,string> indexCreator();

int main(int argc, char* argv[]){
    if(argc!=3){
        cout<<endl<<"ERROR, la ejecucion deberia ser ./nombre path"<< endl;
        return EXIT_FAILURE;
    }
    string index_path = argv[1];
    string process_path = argv[2];
    return EXIT_SUCCESS;
}

map<string, string>indexCreator(){
    map<string,string> pepe;
    pepe["pablo"] = "peine";
    return pepe;
}

// void procesa(string carpetaP, string carpetaR, string extension) {
//     extension = "." + extension;
//     // Itera a través de todos los archivos con en la carpeta indicada a procesar
//     //obs: "auto" te permite declarar variables sin especificar explícitamente su tipo
//     for (const auto& entrada : filesystem::directory_iterator(carpetaP)) {
//         if (entrada.path().extension() == extension) {
//             //cout << "Nombre del archivo: " << entrada.path().filename() << endl;

//             ifstream archivoEntrada(entrada.path());  // Abre el archivo para procesarlo (lo abre modo lectura)

//             if (!archivoEntrada) { // Verifica si el archivo se abrió correctamente
//                 cerr << "No se pudo abrir el archivo para lectura." << endl;
//                 continue; //instrucción de control de flujo en los bucles que sirve para saltarse el resto del código dentro del 
//                         //bucle para la iteración actual y pasar inmediatamente a la siguiente iteración.
//             }
//             string linea;
//             while (getline(archivoEntrada, linea)) { // Lee el archivo línea por línea
//                 // Aqui puedes hacer lo que sea con la linea
//                 istringstream stream(linea); // Convierte la línea en un stream para procesar palabra por palabra
//                 string palabra;
//                 while (stream >> palabra) { // Extrae cada palabra de la línea
//                     //aqui puedes hacer algo con la palabra donde estas posicionado
//                 }
//             }
//             archivoEntrada.close();

//         }
//     } 
// }