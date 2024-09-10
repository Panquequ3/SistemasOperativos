#include <iostream>
#include <string>
#include <cstdlib>   // Para exit
#include <laserpants/dotenv/dotenv.h> // Para las variables de entorno .env
#include "userValidator.h"
using namespace std;

/**
 * @brief comprueba si el nombre de usuario cumple las condiciones
 *
 * @details verifica que el tamaño sea mayor o igual a 3, de serlo comprueba si solo tiene letras
 *
 * @param usuario Nombre de usuario a ser analizado
 * @return Verdadero si cumple las condiciones, Falso si no
 */
bool compruebaUsuario(string usuario){
    int tam = usuario.length();
    if(tam >= 3){
        for (char carac : usuario)
            if(!isalpha(carac)) return false;
    }
    else
        return false; 
    
    return true;
}

/**
 * @brief comprueba si la contraseña del usuario cumple las condiciones
 *
 * verifica que el tamaño sea mayor o igual a 6, de serlo comprueba si solo tiene letras y/o numeros
 *
 * @param pass Contraseña a ser analizada
 * @return Verdadero si cumple las condiciones, Falso si no
 */
bool compruebaContrasena(string pass){
    int tam = pass.length();
    if(tam >= 6){
        for (char carac : pass)
            if(!isalnum(carac)) return false;
    }
    else   
        return false;

    return true;
}

//comprueba los datos ingresados para validar el usuario
/**
 * @brief comprueba si el usuario y contraseña cumplan las condiciones, de ser así, comprueba si 
 * es un usuario valido para acceder 
 *
 * @param username nombre de usuario a ser analizado
 * @param password Contraseña a ser analizada
 */
void compruebaDatos(string username, string password){
    int numUser;
    //inicializacion del .env
    dotenv::init();
    //obs : con c_str, pasamos el string a const char*
    //Verificando que los datos ingresados sean correctos---------------------
    if (!compruebaUsuario(username)) {
        cout << "Formato de usuario no válido" << endl;
        exit(1);
    } else {
        string user = "USER1_NAME";
        numUser = 1;
        // Buscamos al usuario en las variables de entorno
        while (!dotenv::getenv(user.c_str()).empty() && dotenv::getenv(user.c_str()) != username) {
            numUser++;
            user = "USER" + to_string(numUser) + "_NAME";
        }
        // Si es vacío, significa que no se encontró al usuario
        if (dotenv::getenv(user.c_str()).empty()) {
            cout << "El usuario o contraseña son incorrectos" << endl;
            exit(1);
        }
    }
    //comprobamos si la contraseña ingresada es correcta
    if (!compruebaContrasena(password)) {
        cout << "Formato de contraseña no válido" << endl;
        exit(1);
    } else {
        string pass = "USER" + to_string(numUser) + "_PASSWORD"; 
        if (dotenv::getenv(pass.c_str()) != password) {
            cout << "El usuario o contraseña son incorrectos" << endl;
            exit(1);
        }
    }
}