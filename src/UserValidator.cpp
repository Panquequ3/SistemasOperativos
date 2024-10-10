#include <iostream>
#include <string>
#include <utility> // Para cosas mias jijis uwu
#include <map> // Para el HashMap
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

/**
 * @brief Comprueba si el usuario esta en la base de datos
 * @details Verifica si el usuario ingresado pertenence a la "base de datos", dando tambien su rol en forma de entero
 * @param user Nombre de usuario
 * @param password Clave del usuario
 * @param path Path de donde se encuentra el archivo
 * @return 0 si no es usuario, 1 si es un usuario normal y 2 si es admin
 */
int validateUser(string user, string password,string path){
    map<string, pair<string,string>>users = getUsers("",path);
    if(users.find(user)!=users.end()){
        if(users[user].second==password){
            return (users[user].first.compare("Admin")?2:1);
        }
    }
    return 0;
}


/**
 * @brief retorna el rol del usuario
 * @details Verifica si el usuario ingresado pertenence a la "base de datos", dando su rol
 * @param user Nombre de usuario
 * @param path Path del archivo del usuario
 * @return 0 si no es usuario, 1 si es un usuario normal y 2 si es admin
 */
int rolUser(string user,string path){
    map<string,pair<string, string>>users=getUsers("",path);
    if(users.find(user)!=users.end()) return (users[user].first.compare("Admin")?2:1);
    return 0;
}

/**
 * @brief Comprueba que ya exista un usuario
 * @details Verifica si un usuario especifico ya estea presente en la "base de datos"
 * @param user Usuario a buscar
 * @param path Path del archivo del usuario
 * @return verdadero si lo encontro, falso si no
 */
bool findUser(string user,string path){
    map<string,pair<string,string>>users=getUsers("",path);
    return (users.find(user)!=users.end());
}

/**
 * @brief Consigue todos los usuarios y puede excluir a uno
 * @details Extrae todos los usuarios de la "base de datos" y puede no tomar uno
 * @param exclude Usuario excluido de la busqueda
 * @param userpath Path de la informacion de los usuarios
 * @return Un vector con los usuarios dentro de la "base de datos"
 */
map<string,pair<string,string>>getUsers(string exclude,string userpath){
    string name="", rol = "", password = "";
    size_t start,end;
    map<string,pair<string,string>> users;
    ifstream file(userpath);
    if(!file.is_open()){
        cout<<"Error al cargar el archivo!!"<<endl;
        exit(EXIT_FAILURE);
    }
    string temp;
    while(getline(file,temp)){
        start = end = 0;
        end = temp.find(";",start);
        name = temp.substr(start,end-start);
        if(exclude!="" && name!= exclude) continue;
        start = end+1;
        end = temp.find(";",start);
        password = temp.substr(start,end-start);
        start = end+1;
        rol = temp.substr(start);
        users[name] = make_pair(rol,password);
    }
    file.close();
    return users;
}

/**
 * @brief Añade un usuario a la "Base de datos"
 * @details Añade un usuario con su contraseña y rol a la "base de datos"
 * @param user Nombre del usuario a ingresar
 * @param password Contraseña del usuario
 * @param rol Rol del usuario (Admin o Usuario General)
 * @param path Path del archivo del usuario
 */
void addUser(string user, string password, string rol,string path){
    if (compruebaUsuario(user) && compruebaContrasena(password) && !findUser(user,path)){
        ofstream file(path,ios::app);
        file << endl << user+";"+password+";"+rol;
        file.close();
        cout<< "el usuario a sido agregado correctamente"<<endl;
    }
    else{
        cout<<"El usuario ya existe o se ingreso incorrectamente!!!"<<endl;
    }
}

/**
 * @brief Elimina un usuario a la "Base de datos"
 * @details Elimina por completo a un usuario de la "base de datos"
 * @param user Nombre del usuario a eliminar
 * @param userpath Path del archivo del usuario
 */
void deleteUser(string user,string userpath){
    if(findUser(user,userpath) && rolUser(user,userpath)!=2){
        map<string,pair<string,string>> temp = getUsers(user,userpath);
        ofstream file(userpath,ios::trunc);
        for(const auto& i:temp){
            file << i.first << ";" << i.second.second << ";"<< i.second.first << endl;
        }
        file.close();
        cout<<"Usuario "<<user<<" Eliminado"<<endl;
    }
    else{
        cout<<"Usuario no encontrado!!"<<endl;
    }
}
/**
 * @brief Muestra a los usuarios con su rol
 * @param path Path del archivo del usuario
 */
void showUser(string path){
    map<string,pair<string,string>>users=getUsers("",path);
    cout << "Usuarios ------ Rol"<<endl;
    for(const auto& i:users){
        cout<< i.first << "   " << i.second.first << endl;
    }
}