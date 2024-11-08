#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <laserpants/dotenv/dotenv.h>

using namespace std;

const string index_p = "INDEX_PATH";
const string top = "TOPK";

map<string,vector<string>> getIndex(string path);

string extractId(string str);

int extractCant(string str);

string getCoincidence(vector<vector<string>> results, int topk);

string getWords(map<string,vector<string>> index_words, string word,int topk);

int main(){
    dotenv::init();
    string index_path = dotenv::getenv(index_p.c_str());
    int topk = atoi(dotenv::getenv(top.c_str()).c_str());
    map<string,vector<string>> index = getIndex(index_path);
    /*
    Aqui va lo de socket

    
    */
    return 0;
}

map<string,vector<string>> getIndex(string path){
    string word="";
    size_t start,end;
    map<string, vector<string>> words;
    ifstream file(path);
    if(!file.is_open()){
        cout<<"Error al cargar el archivo!!"<<endl;
        exit(EXIT_FAILURE);
    }
    string temp,aux;
    vector<string> id;
    while(getline(file,temp)){
        start = end = 0;
        end = temp.find(";",start);
        word = temp.substr(start,end-start);
        start = end+1;
        end = temp.find(";",start);
        aux = temp.substr(start,end-start);
        while(aux.empty()){
            id.push_back(aux);
            start = end+1;
            end = temp.find(";",start);
            aux = temp.substr(start,end-start);
        }
        words[word] = id;
        id.clear();
    }
    file.close();
    return words;
}

string extractId(string str) {
    size_t start = str.find('(');
    size_t end = str.find(',');
    if (start != string::npos && end != string::npos) {
        return str.substr(start + 1, end - start - 1); // Extraer el id (entre '(' y ',')
    }
    return ""; // Retornar vacío si no se encuentra un formato válido
}

int extractCant(string str){
    size_t start;
    start= str.find(',');
    if(start!=string::npos){
        return atoi(str.substr(start+1).c_str());
    }
    return -1;
}

string getCoincidence(vector<vector<string>> results,int topk){
    vector<pair<string,int>> temp;
    vector<string> aux = results[0];
    int cant = 0;
    int cant_vect = results.size() - 1;
    string str = "";
    for(string i:aux){
        cant = extractCant(i);
        for(int j = 1; j<results.size();j++){
            for(string k:results[j]){
                if(extractId(i).compare(extractId(k))){
                    cant+= extractCant(k);
                    break;
                }
            }
        }
        if(cant!=0) temp.push_back(make_pair(i,cant));
        cant = 0;
    }
    if(temp.empty()) return "E! Ningun libro con la palabra";

    sort(temp.begin(), temp.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    for(int i = 0; i!= topk && i<=temp.size();i++){
        str+=";("+temp[i].first+","+to_string(temp[i].second)+")";
    }
    return str;
}

string getWords(map<string,vector<string>> index_words, string word,int topk){
    vector<string> words;
    vector<string> repeats;
    size_t start,end;
    istringstream iss(word);
    string aux;
    while(iss>>aux){
        words.push_back(aux);
    }
    vector<vector<string>> temp;
    for(string i: words){
        if(index_words.find(i)!=index_words.end())
        temp.push_back(index_words[i]);
        else return ("E! No se encontro " + i +" dentro del archivo");
    }
    return word+getCoincidence(temp,topk); 
}