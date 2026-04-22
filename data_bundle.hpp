#ifndef DATA_BUNDLE_HPP
#define DATA_BUNDLE_HPP

#include <string>
#include <unordered_map>

using namespace std;

struct BookBundle
{
    unordered_map<string, string> centralIndex;
    unordered_map<string, string> authors;
    unordered_map<string, int> years;
    unordered_map<string, string> publishers;
};

struct MemberBundle
{
    int nextId;
    unordered_map<string, string> users; // id, name
    unordered_map<string, string> borrows; // book id, mem id
};

#endif