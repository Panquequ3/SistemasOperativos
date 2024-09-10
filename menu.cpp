#include <iostream>  
#include <vector>     // Para vector
#include <limits>     //para ver un ingreso incorrecto en un cin
#include "funciones.h"//funciones necesarias para el menu y otras
#include "menu.h"
#include <string>
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
    cout << "6) salir" << endl;
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

    while (opcion != 6){
        //capta si hay algun ingreso que genere error
        while (cin.fail() || opcion < 1 || opcion > 6) { 
            cin.clear(); // Limpiar el estado de error del ingreso
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada no válida
            cout << "La opción ingresada no existe, por favor escoja una opción válida: ";
            cin >> opcion;
        }
        if(opcion == 6) break;

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
        cout << "\n¿Desea realizar otra acción? porfavor escoja una opción: ";
        cin >> opcion;
    }
    cout << "\n\tHasta pronto!\n" << endl;
}
