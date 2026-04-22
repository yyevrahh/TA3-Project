#ifndef FILE_HELPER_HPP
#define FILE_HELPER_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "data_bundle.hpp"

using namespace std;

//TODO: refactor update.

void initAllData(BookBundle&, MemberBundle&);   // for initializing all data into maps
void updateGenresFile(BookBundle&);            
void updateFileByDataMapStr(string, unordered_map<string, string>&);
void updateFileByDataMapYears(string, const BookBundle&);
int getNext(string);
bool saveAllData(BookBundle&, MemberBundle&);

#endif
