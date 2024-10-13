#include <iostream>  
#include <vector>     // Para vector
#include <limits>     //para ver un ingreso incorrecto en un cin
#include "funciones.h"//funciones necesarias para el menu y otras
#include "menuContador.h" //para el programa contador de palabras
#include "menu.h"
#include "userValidator.h" //para las cosas del usuarios
#include <string>
#include <unistd.h>   // getpid()
#include <unistd.h>   // Para fork()


using namespace std;



/**
 * @brief Funcion que imprime el menu
 * 
 * @param rol El rol del usuario que añade mas opciones en caso de ser necesario
 */
void imprimeMenu(int rol){
    
    cout << "\n  <<--------MENU-------->>" << endl;
    cout << "0) salir" << endl;
    cout << "1) detección de palíndromos" << endl;
    cout << "2) contar vocales" << endl;
    cout << "3) cantidad de letras en un texto" << endl;
    cout << "4) promedio y sumatoria de un vector" << endl;
    cout << "5) calcular f(x)=5x*x+1/x" << endl;
    cout << "6) programa contador de palabras" << endl;
    cout << "7) conteo paralelo con threads" << endl;
    cout << "8) creación indice invertido"<<endl;
    if(rol==2){
        cout << "9) Añadir un usuario" << endl;
        cout << "10) Lista de usuarios" << endl;
        cout << "11) Eliminar un usuario" << endl;
    }
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
void seleccionMenu(string texto, vector<int> numeros, float numero,string username, int rol,
    string user_path, string result_path, string process_path, string map_path,string index_path,
    string temp_path, string ext_archive,string cant_threads,string stop_path){

    imprimeMenu(rol);
    int moreoptions = (rol==2)? 3 : 0 ;
    bool isProcessed = false;
    int opcion;
    cout << "¡bienvenido! seleccione la opción deseada: ";
    cin >> opcion;

    while (true){
        //.fail() capta si hay algun ingreso que genere error, en este caso que se ingrese algo que no es un numero
        //esta entrada fallida queda en un buffer
        while (cin.fail() || opcion < 0 || (opcion > 8+moreoptions)) { 
            cin.clear(); // Limpiar el estado de error del ingreso (reestablece el estado de cin)
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada no válida (descarta lo que hay en el buffer)
            cout << "La opción ingresada no existe, por favor escoja una opción válida: ";
            cin >> opcion;
        }
        if(opcion == 0) break;

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
            system("clear");

            // Ejecutar el programa después de que se haya compilado
            system("./mainContador");
            imprimeMenu(rol);
        }
        if(opcion == 7){
            string command = "./paralelo " + cant_threads + " " + process_path + " " + result_path + " " + ext_archive + " " + stop_path + " " + temp_path + " " + map_path;
            int temp = system(command.c_str());
            isProcessed = temp==0;
        }
        if(opcion == 8){
            if(isProcessed){
                string command_i = "./index "+index_path+ " "+result_path;
                int temp_2 = system(command_i.c_str());
                if(temp_2==0){
                    cout <<"la ejecucion del programa fue un exito."<< endl<<"La ruta del indice es "<<index_path<<endl;
                }
                else{
                    cout<< "Error al ejecutar la opcion 8"<<endl;
                }
            }
            else{
                cout <<"El proceso de la opcion 7 no fue ejecutado"<<endl <<"ejecutalo antes de volver a usar esta opcion"<<endl;
            }
        }
        if(opcion == 9){
            string temp_usr = "",temp_psw,temp_rol;
            
            cout<<endl<<"Nombre de usuario: ";
            cin >> temp_usr;

            cout << endl << "Contraseña: ";
            cin>>temp_psw;

            cout<<endl<<"Rol del usuario(Admin o Usuario): ";
            cin>>temp_rol;
            do{
                cout<<endl<<"El usuario debe ser Admin o Usuario"<<endl<<"Rol del usuario(Admin o Usuario): ";
                cin>>temp_rol;
            }while(!(temp_rol=="Admin" || temp_rol=="Usuario"));
            
            addUser(temp_usr,temp_psw,temp_rol,user_path);
        }
        if(opcion == 10){
            showUser(user_path);
        }
        if(opcion == 11){
            string temp_usr = "";
            do{
                cout<<endl<<"Ingrese usuario a eliminar: ";
                cin>> temp_usr;
            }while(username==temp_usr);
            deleteUser(temp_usr,user_path);
        }
        cout << "\n¿Desea realizar otra acción? porfavor escoja una opción: ";
        cin >> opcion;
    }
    cout << "\n\tHasta pronto!\n" << endl;
}
