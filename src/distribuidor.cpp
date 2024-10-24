#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "distribuidor.h"
using namespace std;

vector<string> interpreteMsg(string msg){
    //lista de los elementos ya separados
    //su forma es {core, id, operacion, num1, num2}
    vector<string>list; 

    // limpiamos el str de los parentesis

    if (msg.front() == '(' && msg.back() == ')') {
        msg.erase(msg.size() - 1, 1); // Elimina el último carácter
        msg.erase(0, 1); // Elimina el primer carácter
    }else{
        cout << "Error, no se respetó la forma del mensaje" << endl;
        return list;
    }

    // comenzamos a almacenar el resto
    string aux = "";
    int i = 0;

    // almacenamos el core
    while(msg[i] != ':')
        i++;
    list.push_back(msg.substr(0,i));
    msg = msg.substr(i+1); //trabajaremos con el str restante
    aux = "";
    i = 0;

    // almacenamos el id de la operacion
    while(msg[i] != ';')
        i++;
    list.push_back(msg.substr(0,i));
    msg = msg.substr(i+1); //trabajaremos con el str restante (Error_1)
    aux = "";
    i = 0;

    // almacenamos la operacion
    while(msg[i] != ';'){
        aux = aux + msg[i];
        i++;
    }
    list.push_back(aux);

    //tomamos la parte que queremos procesar, añadimos una ',' para procesar los numeros
    msg = msg.substr(i+1) + ",";
    aux = ""; 

    // almacenamos los numeros
    for(char c : msg){
        if(c != ',')
            aux = aux + c;
        else{
            list.push_back(aux); //los añadimos a la lista
            aux = "";
        }
    }
    for (string elem : list) {
        cout << elem << endl;
    }
    cout << endl;
    return list; 
}
// corePath es la carpeta temp
void distributeToCore(string msg, string resultPath = "./data/planificador/resultados.txt" , string corePath = "./data/temporal"){
    vector<string> data = interpreteMsg(msg); //{core, id, operacion, num1, num2}
    string command = "./core " + data[2] + " " + data[3] + " " + data[4];
    // esto es "./core suma 10 1", system(./core operation num1 num2)
    //float result = system(aki ponele)
    string result = "0"; //mientras aun no está core implementado
    
    // abrimos el archivo para escribir en el (añadiendo, no sobrescribiendo)

    // pense que los archivos temporales eran para ver la informacion resultante, debido a que si es secuencial, deberiamos traducir lo de system
    ofstream resultArc(resultPath, ios::app);

    if(!resultArc){
        cerr << "Error, no se pudo abrir el archivo para escritura" << endl;
        return;
    }

    resultArc << msg + "=>" + result << endl;

    resultArc.close();
    // ----------------- Cambiamos el estado del core utilizado ------------------------------
    ofstream coreArc(corePath + "/" + data[0] + ".txt");
    if(!coreArc){
        cerr << "Error, no se pudo abrir el archivo, revise el path ingresado e intentelo nuevamente" << endl;
    }
    coreArc.seekp(0); // Mover el puntero de escritura al inicio del archivo
    coreArc.put('1'); // Cambiamos su estado a ocupado
    coreArc.close();
    // ------------------------------------------------------------------------
}