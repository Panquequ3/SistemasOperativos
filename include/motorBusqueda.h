#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

map<string,vector<string>> getIndex(string path);

string extractId(string str);

int extractCant(string str);

string getCoincidence(vector<vector<string>> results, int topk);

string getWords(map<string,vector<string>> index_words, string word,int topk);