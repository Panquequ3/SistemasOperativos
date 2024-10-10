#include "funciones.h" //funciones necesarias para el menu y otras
#include "menu.h" //para ejecutar el menu
#include "userValidator.h" //para validar que el usuario ingresado es correcto
#include <unistd.h>  // Para getopt
#include <vector>    // Para vector
#include <string>    // Para string
#include <cstdlib>   // Para exit y los .env
#include <getopt.h> //para los argumentos del programa
#include <exception> //para las excepciones
#include <laserpants/dotenv/dotenv.h> //para las variables de entorno .env
#include <iostream>
#include <cstdlib>

const string USERS = "USERS_PATH";
const string RESULT = "RESULT_PATH";
const string PROCESS = "PROCESS_PATH";
const string THREADS = "CANT_THREADS";
const string MAP = "MAP_PATH";
const string INDEX = "INDEX_PATH";
const string EXT = "EXT_ARCHIVE";
const string TEMP = "TEMP_PATH";
const string STOP = "STOP_PATH";

using namespace std;


//Aquí comienza el programa
int main(int argc, char* argv[]) {
    //inicialización de variables
    string username, password, frase; 
    vector<int> numeros;
    int opt;
    float numero;
    bool isUser = false, isPass = false, isFrase = false, isNum = false, isN = false;
    

    //leyendo los argumentos del programa, si alguno no fue proporcionado, el programa se cerrará
    while ((opt = getopt(argc, argv, "u:p:t:v:n:")) != -1) {
        switch (opt) {
            //El argumento -u, permite ingresar un nombre de usuario
            case 'u':
                username = optarg;
                isUser = true;
                break;
            //El argumento -p, permite ingresar de la contraseña del usuario
            case 'p':
                password = optarg;
                isPass = true;
                break;
            //El argumento -t, debe permitir en ingreso de una frase
            case 't':
                frase = optarg;   
                isFrase = true;     
                break;
            //El argumento -v, permite pasar al sistema un vector de número entero
            case 'v':            
                numeros = split(optarg);
                isNum = true;
                break;
            //El argumento -n, permite el ingreso de un número
            case 'n':  
                string aux = optarg;
                for (char car : aux){
                    if (car != '.' && !isdigit(car)) {
                        cerr << "\nError: '" << aux << "' no es un número válido, por favor, ingrese valores correctos\n" << endl;
                        exit(1);
                    }
                } 
                numero = atof(optarg);  // Convierte la cadena a entero
                isN = true;
                break;
        }
    }    

    // Comprobación después del procesamiento de argumentos
    if (!isUser) {
        cout << "\nError. El parámetro -u no fue proporcionado." << endl;
		cout << "Recuerda, debe ejecutarse como: ./miPrograma -u user -p password -t text -v numbers -n number\n" << endl;
        exit(1);
    }if (!isPass) {
        cout << "\nError. El parámetro -p no fue proporcionado." << endl;
		cout << "Recuerda, debe ejecutarse como: ./miPrograma -u user -p password -t text -v numbers -n number\n" << endl;
        exit(1);
    }if (!isFrase) {
        cout << "\nError. El parámetro -t no fue proporcionado." << endl;
		cout << "Recuerda, debe ejecutarse como: ./miPrograma -u user -p password -t text -v numbers -n number\n" << endl;
        exit(1);
    }if (!isNum) {
        cout << "\nError. El parámetro -v no fue proporcionado." << endl;
        cout << "Recuerda, debe ejecutarse como: ./miPrograma -u user -p password -t text -v numbers -n number\n" << endl;
        exit(1);
    }if (!isN) {
        cout << "\nError. El parámetro -n no fue proporcionado." << endl;
		cout << "Recuerda, debe ejecutarse como: ./miPrograma -u user -p password -t text -v numbers -n number\n" << endl;
        exit(1);
    }
    //Inicializacion de las cosas del .env y para pasarlas directo al programa principal uwu <3
    dotenv::init();

    string user_path = dotenv::getenv(USERS.c_str());
    string result_path = dotenv::getenv(RESULT.c_str());
    string process_path = dotenv::getenv(PROCESS.c_str());
    string map_path = dotenv::getenv(MAP.c_str());
    string index_path = dotenv::getenv(INDEX.c_str());
    string temp_path = dotenv::getenv(TEMP.c_str());
    string ext_archive = dotenv::getenv(EXT.c_str());
    string cant_threads = dotenv::getenv(THREADS.c_str());
    string stop_path = dotenv::getenv(STOP.c_str());

    //Verificacion del usuario

    int rol = validateUser(username,password,user_path);

    if(rol==0){
        cout<<"\nError, la contraseña o el usuario es incorrecto!"<<endl;
        exit(EXIT_FAILURE);
    }
    
    //------------------------------------------------------------------------
    // Imprimir resultados para verificación
    cout << "\n<>--------------------------------<>" << endl;
    cout << "PID = " << getpid() << endl;
    cout << "LOS DATOS INGRESADOS FUERON: " << endl;
    cout << "Usuario: " << username << endl;
    cout << "Rol: "<< ((rol==2)?"Admin":"Usuario General") << endl;
    cout << "Frase: " << frase << endl;
    cout << "Números: ";
    for (int num : numeros) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Número: " << numero << endl;
    cout << "<>---------------------------------<>\n" << endl;
    seleccionMenu(frase, numeros, numero,username,rol,
        user_path,result_path,process_path,map_path,index_path
        ,temp_path,ext_archive,cant_threads,stop_path);
    return 0;
}
