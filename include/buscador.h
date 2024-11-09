#include <iostream> 
#include <string> 
#include <vector>
#include "motorBusqueda.h"
using namespace std;

void searcher(string outputWord);
vector<string> split(string str);
string searchOnMap(string mapPath, string id);
string translate(string answer, string mapPath);