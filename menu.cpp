#include <iostream>  
#include <vector>     // Para vector
#include <limits>     //para ver un ingreso incorrecto en un cin
#include "funciones.h"//funciones necesarias para el menu y otras
#include "menuContador.h" //para el programa contador de palabras
#include "menu.h"
#include <string>
#include <unistd.h>   // Para fork()
#include <sys/wait.h> // Para wait()


using namespace std;



/**
 * @brief Funcion que imprime el menu
 * 
 */
void imprimeMenu(){
    cout << "\n  <<--------MENU-------->>" << endl;
    cout << "1) detección de palíndromos" << endl;
    cout << "2) contar vocales" << endl;
    cout << "3) cantidad de letras en un texto" << endl;
    cout << "4) promedio y sumatoria de un vector" << endl;
    cout << "5) calcular f(x)=5x*x+1/x" << endl;
    cout << "6) programa contador de palabras" << endl;
    cout << "7) salir" << endl;
    cout << "  <<-------------------->>\n" << endl;
}

//Da las opciones del menu y ejecuta la opción que pida el usuario
/**
 * @brief Permite la seleccion de las opciones del menu, dependiendo del numero se ejecutara la función correspondiente
 * 
 *
 * 
 * @param texto parametro a utilizar en las opciones (1) (2) y (3)
 * @param numeros parametro a utilizar en la opcion (4)
 * @param numero parametro a utilizar en la opcion (5)
 * 
 */
void seleccionMenu(string texto, vector<int> numeros, float numero){

    imprimeMenu();

    int opcion;
    cout << "¡bienvenido! seleccione la opción deseada: ";
    cin >> opcion;

    while (opcion != 7){
        //.fail() capta si hay algun ingreso que genere error, en este caso que se ingrese algo que no es un numero
        //esta entrada fallida queda en un buffer
        while (cin.fail() || opcion < 1 || opcion > 7) { 
            cin.clear(); // Limpiar el estado de error del ingreso (reestablece el estado de cin)
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada no válida (descarta lo que hay en el buffer)
            cout << "La opción ingresada no existe, por favor escoja una opción válida: ";
            cin >> opcion;
        }
        if(opcion == 7) break;

        //opciones validas
        if(opcion == 1){
            if (esPalindrome(texto))
                cout << texto << " es palindrome! " << endl; 
            else 
                cout << texto << " no es palindrome.." << endl; 
        }   
        if(opcion == 2)
            cout << "La cantidad de vocales en el texto ingresado es : " << cuentaVocal(texto) << endl;
        if(opcion == 3)
            cout << "La cantidad de letras en el texto ingresado es : " << cantidadLetras(texto) << endl;
        if(opcion == 4){
            cout << "El promedio de los numeros ingresados es : " << promSum(numeros)[0] << endl;
            cout << "La sumatoria de los numeros ingresados es : " << promSum(numeros)[1] << endl;
            }
        if(opcion == 5){
            cout << "El resultado de f(" << numero << ") es :" << endl;
            f(numero);
            }
        if(opcion == 6){
            // Llamar a make para compilar programa cuenta palabras
            system("make -f MakefileC");
            system("clear");

            // Ejecutar el programa después de que se haya compilado
            system("./mainContador");
            imprimeMenu();

        }
        cout << "\n¿Desea realizar otra acción? porfavor escoja una opción: ";
        cin >> opcion;
    }
    cout << "\n\tHasta pronto!\n" << endl;
}
