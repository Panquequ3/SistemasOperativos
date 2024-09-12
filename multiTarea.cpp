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
    dotenv::init();
    int rol = validaUser(username,password);
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
    seleccionMenu(frase, numeros, numero,username,rol);

    return 0;
}
