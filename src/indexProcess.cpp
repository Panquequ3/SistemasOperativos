#include <iostream>
#include <map>

using namespace std;

map<string,string> indexCreator();

int main(int argc, char* argv[]){
    if(argc!=3){
        cout<<endl<<"ERROR, la ejecucion deberia ser ./nombre path"<< endl;
        return EXIT_FAILURE;
    }
    string index_path = argv[1];
    string process_path = argv[2];
    return EXIT_SUCCESS;
}

map<string, string>indexCreator(){
    map<string,string> pepe;
    pepe["pablo"] = "peine";
    return pepe;
}