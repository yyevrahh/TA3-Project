#ifndef DATA_HELPER_HPP
#define DATA_HELPER_HPP

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int getGenreCount(const string&, const unordered_map<string, string>&);
void getPlacement(int, int&, int&);
string generateMemberID(int);

#endif