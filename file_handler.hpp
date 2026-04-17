#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


void readAndAppend(string, unordered_map<string, string>&);
void initToCentralIndex(unordered_map<string, string>&);
void writeIntoFile(string, string);
void updateGenresFile(unordered_map<string, string>&);

#endif