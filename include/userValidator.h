#include <iostream>
#include <string>

using namespace std;
//comprueba si el nombre de usuario cumple las condiciones
bool compruebaUsuario(string usuario);
//comprueba si la contrasena cumple las condiciones
bool compruebaContrasena(string pass);
//comprueba los datos ingresados para validar el usuario
int validaUser(string user, string password);
//busca el usuario
bool encuentraUsuario(string user);
//consigue los usuarios (para encuentra y elimina)
vector<string> getUsers(string exclude);
//añade un usuario a la base de datos
void addUser(string user, string password, string rol);
//elimina un usuario de la base de datos
void deleteUser(string user);
//saca el rol de un usuario
int rolUser(string user);
//muestra a los usuarios
void showUser();