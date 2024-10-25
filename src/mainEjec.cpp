#include <iostream>
#include <vector>
#include <string>
#include "ejecutador.h"

using namespace std;

int main(int argc, char* argv[]){
    //En caso de reutilizarlo en otra parte
	if(argc != 11){
		cout << "Error. Debe ejecutarse como ./ejec arrayThreads repeticiones datos grafico pathP pathR extension pathStopWord pathTemp mapPath" << endl;
		exit(EXIT_FAILURE);
	}
    string array = argv[1];
    int repeats = atoi(argv[2]);
    string dataOutput = argv[3];
    string graphic = argv[4];
    // --------------------
    string pathP = argv[5];
    string pathR = argv[6];
    string ext = argv[7];
    string stopWord = argv[8];
    string temp = argv[9];
    string map = argv[10];
    // resto del comando que necesita el ejecutador
    string cmd = pathP + " " + pathR + " " + ext + " " + stopWord + " " + temp + " " + map;
    vector<int>threads;
    // int num;
    array += ',';
    string aux = "";
    for(char elem : array){
        if (elem != ',')
            aux = aux + elem;
        else{
            threads.push_back(stoi(aux));
            aux = "";
        }
    }
    
    for(int thread : threads){
        ejecute(thread, cmd, repeats, dataOutput);
    }

}