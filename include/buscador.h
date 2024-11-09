#include <iostream> 
#include <string> 
#include <vector>
#include "motorBusqueda.h"
using namespace std;

void startClient(string map_path,string outputWord);
void searcher(string outputWord);
void printResults(vector<string> vec);
vector<string> split(string str);
string searchOnMap(string mapPath, string id);
string translate(string answer, string mapPath);