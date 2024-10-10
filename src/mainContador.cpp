#include "menuContador.h" //para ejecutar el menu
#include <unistd.h>  // Para getpid()
#include <iostream>

using namespace std;

int main(){
    // Este es el proceso hijo
    seleccionMenuCont(); // El hijo llama a una función propia
    return 0;
}