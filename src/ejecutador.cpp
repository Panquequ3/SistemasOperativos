#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    //En caso de reutilizarlo en otra parte
	if(argc != 5){
		cout << "Error. Debe ejecutarse como ./ejec arrayThreads repeticiones datos grafico" << endl;
		exit(EXIT_FAILURE);
	}
    string array = argv[1];
    int repeats = atoi(argv[2]);
    string data = argv[3];
    string ext = argv[4];
    string graphic = argv[5];

}