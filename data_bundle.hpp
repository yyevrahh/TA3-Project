#ifndef DATA_BUNDLE_HPP
#define DATA_BUNDLE_HPP

#include <string>
#include <unordered_map>

using namespace std;

struct BookBundle
{
    // book id: GEN0101
    unordered_map<string, string> centralIndex; // id : title
    unordered_map<string, string> authors;      // id : author
    unordered_map<string, int> years;           // id : year
    unordered_map<string, string> publishers;   // id : publisher
};

struct MemberBundle
{
    int nextId;                          // to avoid member id collision
    unordered_map<string, string> users; // member id : name
    unordered_map<string, string> borrows; // book id : mem id
};

#endif