#ifndef FILE_HELPER_HPP
#define FILE_HELPER_HPP

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void readAndAppend(string, unordered_map<string, string>&);
void initToCentralIndex(unordered_map<string, string>&);
void updateGenresFile(unordered_map<string, string>&, unordered_map<string, string>&, unordered_map<string, int>&, unordered_map<string, string>&);
void updateFileByDataMapStr(string, unordered_map<string, string>&);
void updateFileByDataMapInt(string, unordered_map<string, int>&);

#endif
