#include <iostream>
#include <map>
#include <fstream>
#include <filesystem> //para explorar archivos en una carpeta

using namespace std;

void indexCreator(string process_path,string index_path);

int main(int argc, char* argv[]){
    if(argc!=3){
        cout<<endl<<"ERROR, la ejecucion deberia ser ./nombre path"<< endl;
        return EXIT_FAILURE;
    }
    string index_path = argv[1];
    string process_path = argv[2];
    indexCreator(process_path,index_path)
    return EXIT_SUCCESS;
}

void indexCreator(string process_path,string index_path){
    map<string,string> words;
    size_t end;
    string temp;
    string word;
    string cant;
    string id;
    for (const auto& input : filesystem::directory_iterator(process_path)) {
        if (input.path().extension() == ".txt") {
            ifstream inputFile(input.path());
            if (!inputFile) { // Verifica si el archivo se abrió correctamente
                cerr << "No se pudo abrir el archivo para lectura." << endl;
                continue; 
            }
            id = input.path().stem().string();
            while (getline(inputFile, temp)) {
                //muere con palabras que sean del tipo asdas;;
                end = 0;
                end = temp.find(";");
                word = temp.substr(0,end);
                end++;
                cant = temp.substr(end);
                if(words.find(word)==words.end()){
                    words[word] = "("+id+","+cant+");";
                }
                else{
                    words[word] = words[word]+"("+id+","+cant+");";
                }
            }
            inputFile.close();
        }
    }
    ofstream file(index_path,ios::trunc);
    for(const auto& i:words){
        file << i.first << ";" << i.second << endl;
    }
    file.close();
    return words;
}