#ifndef FILE_HELPER_HPP
#define FILE_HELPER_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "data_bundle.hpp"

using namespace std;

void initAllData(BookBundle& books);
void updateGenresFile(BookBundle&);
void updateFileByDataMapStr(string, unordered_map<string, string>&);
void updateFileByDataMapInt(string, const BookBundle&);

#endif
