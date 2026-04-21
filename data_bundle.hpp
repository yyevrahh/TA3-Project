#ifndef DATA_BUNDLE_HPP
#define DATA_BUNDLE_HPP

#include <string>
#include <unordered_map>

using namespace std;

struct BookBundle {
    unordered_map<string, string> centralIndex;
    unordered_map<string, string> authors;
    unordered_map<string, int> years;
    unordered_map<string, string> publishers;
};

#endif