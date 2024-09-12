#include <iostream>  
#include <vector>     // Para vector
#include <limits>     //para ver un ingreso incorrecto en un cin
#include "contadorPalabras.h"//funciones necesarias para el menu y otras
#include "menuContador.h"
#include <unistd.h>   // getpid()
#include <string>
#include <filesystem> //para verificar archivos
using namespace std;



/**
 * @brief Funcion que imprime el menu
 * 
 */
void imprimeMenuCont(){
    cout << "\nPROGRAMA CONTADOR DE PALABRAS" << endl;
    cout << "##################################\n" << endl;
    cout << "PID: " << getpid() << endl;

    cout << "\n  <<--------Seleccione la opcion-------->>" << endl;
    cout << "0) Salir" << endl;
    cout << "1) Extensión de archivos a procesar (ej: txt)" << endl;
    cout << "2) Path de carpeta a procesar (ej: /home/Ivc/in)" << endl;
    cout << "3) Path de carpeta que contendrá la respuesta del proceso (ej: /home/Ivc/out)" << endl;
    cout << "4) Procesar" << endl;
    cout << "  <<-------------------->>\n" << endl;
}

//Da las opciones del menu y ejecuta la opción que pida el usuario
/**
 * @brief Permite la seleccion de las opciones del menu, dependiendo del numero se ejecutara la función correspondiente
 * 
 */
void seleccionMenuCont(){
    string extension, carpetaP, carpetaR;
    bool isP = false, isExt = false, isR = false; //para verificar que los datos hayan sido ingresados antes de procesar
    imprimeMenuCont();

    int opcion;
    cout << "¡bienvenido al contador! seleccione la opción deseada: ";
    cin >> opcion;

    while (opcion != 0){
        //.fail() capta si hay algun ingreso que genere error, en este caso que se ingrese algo que no es un numero
        //esta entrada fallida queda en un buffer
        while (cin.fail() || opcion < 0 || opcion > 4) { 
            cin.clear(); // Limpiar el estado de error del ingreso (reestablece el stream)
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada no válida () (descarta lo que hay en el buffer)
            cout << "La opción ingresada no existe, por favor escoja una opción válida: ";
            cin >> opcion;
        }

        switch (opcion){            
            case 0:
                break;
            case 1:
                cout << "Ingrese la extension de los archivos a procesar : ";
                cin >> extension;
                if (extension != "") isExt = true;
                break;
            case 2:
                cout << "Ingrese el path de la carpeta a procesar : ";
                cin >> carpetaP;
                //Comprobamos que el path exista, y que sea una carpeta
                if (filesystem::exists(carpetaP) && filesystem::is_directory(carpetaP)) isP = true;
                else cout << "por favor, ingrese una carpeta existente";

                break;
            case 3:
                cout << "Ingrese el path de la carpeta que contendrá el resultado : ";
                cin >> carpetaR;  
                //Comprobamos que el path exista, y que sea una carpeta
                if (filesystem::exists(carpetaR) && filesystem::is_directory(carpetaR)) isR = true;
                else cout << "por favor, ingrese una carpeta existente";

                break;
            case 4:
                cout << "procesando.. " << endl;
                //si fueron ingresados todos los datos necesarios, procesamos
                if(isExt && isP && isR) 
                    procesa(carpetaP, carpetaR, extension);
                else{
                    if(!isExt) cout << "Falta ingresar la extensión de los archivos" << endl;
                    if(!isR) cout << "Falta ingresar la carpeta donde se ubican los archivos a procesar" << endl;
                    if(!isP) cout << "Falta ingresar la carpeta donde se ubicara el resultado" << endl;
                    cout << "vuelva a intentarlo" << endl;
                }
                break;
        }
        cout << "\n¿Desea realizar otra acción? porfavor escoja una opción: ";
        cin >> opcion;
    }
    cout << "\nvolviendo al programa principal..." << endl;
    cout << "\n\tHasta pronto!\n" << endl;
}
