#include <iostream>
#include <string>
#include <map>
#include <utility>

using namespace std;
//comprueba si el nombre de usuario cumple las condiciones
bool compruebaUsuario(string usuario);
//comprueba si la contrasena cumple las condiciones
bool compruebaContrasena(string pass);
//comprueba los datos ingresados para validar el usuario
int validateUser(string user, string password, string path);
//busca el usuario
bool findUser(string user,string path);
//consigue los usuarios (para encuentra y elimina)
map<string,pair<string,string>> getUsers(string exclude,string userpath);
//añade un usuario a la base de datos
void addUser(string user, string password, string rol,string path);
//elimina un usuario de la base de datos
void deleteUser(string user,string userpath);
//saca el rol de un usuario
int rolUser(string user,string path);
//muestra a los usuarios
void showUser(string path);