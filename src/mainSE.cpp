#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <laserpants/dotenv/dotenv.h>
#include "motorBusqueda.h"

using namespace std;

const string index_p = "INDEX_PATH";
const string top = "TOPK";

int main(){
    /*
    Iniciar el socket
    */
    dotenv::init();
    string index_path = dotenv::getenv(index_p.c_str());
    int topk = atoi(dotenv::getenv(top.c_str()).c_str());
    map<string,vector<string>> index = getIndex(index_path);
    /*
    Esperar y enviar mensajes del servidor
    */
    return 0;
}