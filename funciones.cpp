#include "funciones.h" //funciones necesarias para el menu y otras
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <exception>
#include <vector>

using namespace std;

//definiendo excepciones a utilizar---------------------
class DivisionPorCero : public exception {
public:
    const char* what() const noexcept override {
        return "Error, no es posible dividir por cero";
    }
};
//-------------------------------------------------------

//DEFINICIÓN DE FUNCIONES -------------------------------

/**
 * @brief Verifica si una palabra es palindrome invirtiendola y comparandola con su forma original,
de serlo, entonces retorna verdadero.
 *
 * Esta función calcula el factorial de un número entero positivo utilizando
 * una implementación recursiva.
 *
 * @param palabra La palabra o frase a ser analizada.
 * @return Verdadero si la palabra es palindrome, Falso si no.
 */
bool esPalindrome(string palabra){
    string aux = "";
    //procesamos la palabra sin espacios y en minusculas
    for (char carac : palabra)
        if(carac != ' ')
            aux += tolower(carac);
    //invertimos la palabra para comparar
    string rev = aux;
    reverse(aux.begin(), aux.end());
    //comparamos si son iguales
    if (rev == aux)
        return true;
    return false;
}


/**
 * @brief Cuenta las vocales en un texto.
 *
 * Recorre el texto contando las vocales
 *
 * @param texto El texto a ser analizado.
 * @return La cantidad de vocales en el texto
 */
int cuentaVocal(string texto){
    int contador = 0;
    for (char carac : texto){
        char car = tolower(carac);
        if(car == 'a' || car == 'e' || car == 'i' || car == 'o' || car == 'u')
            contador++;
    }
    return contador;
}


/**
 * @brief Cuenta la cantidad de letras en un texto.
 *
 * Recorre el texto contando las letras
 *
 * @param texto El texto a ser analizado.
 * @return La cantidad de letras en el texto
 */
int cantidadLetras(string texto){
    int contador = 0;
    for (char carac : texto){
        if(isalpha(carac))
            contador++;
    }
    return contador;
}



/**
 * @brief Calcula la sumatoria y el promedio de los valores en un vector.
 *
 *
 * @param numeros Es el vector al que se le calculara la sumatoria y promedio.
 * @return Retorna un vector donde vector[0] = promedio y vector[1] = sumatoria.
 */
vector<int> promSum(vector<int> numeros){
    vector<int> resultado;
    int promedio = 0;
    int sumatoria = 0;
    for(int num : numeros){
        promedio += num;
        sumatoria += num;
    }
    resultado.push_back(promedio/(numeros.size()));
    resultado.push_back(sumatoria);

    return resultado;
}

/**
 * @brief Evalua el valor ingresado en una funcion especifica.
 *
 *
 * @param x Valor a evaluar en la funcion.
 * 
 */
void f(float x){
    float resultado;
    try {
        if(x == 0.0)
            throw DivisionPorCero();
        else{
        resultado = 5*x*x + (1/x);
        cout << resultado << endl;
        }
    } catch (const DivisionPorCero& e) {
        cerr << e.what() << endl;
    }
}


/**
 * @brief función que separa un string de enteros por el simbolo ';'
 *
 *
 * @param str Cadena que será procesada
 * @return Vector de los enteros separados
 */
vector<int> split(string str){
    str = str + ';';

    int tam = str.size();
    vector<int> valores;
    string aux = "";
    for (int i = 0; i < tam; i++){
        if(str[i] != ';'){
            aux += str[i];
            if (!isdigit(str[i])) {
                cerr << "\nError: '" << str[i] << "' no es un número válido, por favor, ingrese valores correctos\n" << endl;
                exit(1);
            }
        }
        else{
            int valor = stoi(aux);
            valores.push_back(valor);
            aux = "";
        }
    }
    
    return valores;
}