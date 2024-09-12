#include <iostream>
#include <string>
#include <vector>
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
 * @return 0 si no es usuario, 1 si es un usuario normal y 2 si es admin
 */
int validaUser(string user, string password){
    size_t ini,fin;
    string temp;
    vector<string>users=getUsers("");
    for(string i:users){
        ini = fin = 0;
        fin = i.find(";",ini);
        temp = i.substr(ini,fin-ini);
        if(temp==user){
            ini=fin+1;
            fin=i.find(";",ini);
            if(fin == string::npos) continue;
            temp = i.substr(ini,fin-ini);
            if(temp==password){
                ini=fin+1;
                string rol = i.substr(ini);
                if(rol.find("Admin")!=string::npos){
                    return 2;
                }
                else{
                    return 1;
                }
            }
            else{
                return 0;
            }
        }
    }
    return 0;
}


/**
 * @brief retorna el rol del usuario
 * @details Verifica si el usuario ingresado pertenence a la "base de datos", dando su rol
 * @param user Nombre de usuario
 * @return 0 si no es usuario, 1 si es un usuario normal y 2 si es admin
 */
int rolUser(string user){
    size_t ini,fin;
    string temp;
    vector<string>users=getUsers("");
    for(string i:users){
        ini = fin = 0;
        fin = i.find(";",ini);
        temp = i.substr(ini,fin-ini);
        if(temp==user){
            ini=fin+1;
            fin=i.find(";",ini);
            if(fin == string::npos) continue;
            temp = i.substr(ini,fin-ini);
            ini=fin+1;
            string rol = i.substr(ini);
            if(rol.find("Admin")!=string::npos){
                return 2;
            }
            else{
                return 1;
            }
        }
    }
    return 0;
}

/**
 * @brief Comprueba que ya exista un usuario
 * @details Verifica si un usuario especifico ya estea presente en la "base de datos"
 * @param user Usuario a buscar
 * @return verdadero si lo encontro, falso si no
 */
bool encuentraUsuario(string user){
    int ini = 0,fin;
    int cont = 0;
    string temp;
    vector<string>users=getUsers("");
    for(string i:users){
        fin = i.find(";",ini);
        temp = i.substr(ini,fin-ini);
        cont++;
        if(temp==user){
            return true;
        }
    }
    return false;
}

/**
 * @brief Consigue todos los usuarios y puede excluir a uno
 * @details Extrae todos los usuarios de la "base de datos" y puede no tomar uno
 * @param exclude Usuario excluido de la busqueda
 * @return Un vector con los usuarios dentro de la "base de datos"
 */
vector<string> getUsers(string exclude){
    string userpath = "USERPATH";
    string path = dotenv::getenv(userpath.c_str());
    vector<string> users;
    ifstream file(path);
    if(!file){
        cout<<"Error al cargar el archivo!!"<<endl;
        exit(EXIT_FAILURE);
    }
    string temp;
    if(exclude==""){
        while(getline(file,temp)){
            users.push_back(temp);
        }
        file.close();
        return users;
    }
    else{
        while(getline(file,temp)){
            if(exclude!=temp.substr(0,temp.find(";"))){
                users.push_back(temp);
            }
        }
        file.close();
        return users;
    }
}

/**
 * @brief Añade un usuario a la "Base de datos"
 * @details Añade un usuario con su contraseña y rol a la "base de datos"
 * @param user Nombre del usuario a ingresar
 * @param password Contraseña del usuario
 * @param rol Rol del usuario (Admin o Usuario General)
 */
void addUser(string user, string password, string rol){
    string userpath = "USERPATH";
    string path = dotenv::getenv(userpath.c_str());
    if (compruebaUsuario(user) && compruebaContrasena(password) && !encuentraUsuario(user)){
        ofstream file(path,ios::app);
        file << user+";"+password+";"+rol<<endl;
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
 */
void deleteUser(string user){
    string userpath = "USERPATH";
    string path = dotenv::getenv((userpath.c_str()));
    if(encuentraUsuario(user) && rolUser(user)!=2){
        vector<string> temp = getUsers(user);
        ofstream file(path,ios::trunc);
        for(string i:temp){
            file << i << endl;
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
 */
void showUser(){
    size_t ini,fin;
    string usr,rol;
    vector<string>users=getUsers("");
    cout << "Usuarios ------ Rol"<<endl;
    for(string i:users){
        ini = fin = 0;
        fin = i.find(";",ini);
        
        usr = i.substr(ini,fin-ini);
        ini=fin+1;
        fin=i.find(";",ini);
        ini=fin+1;
        rol = i.substr(ini);
        cout<< usr << "   " << rol << endl;
    }
}