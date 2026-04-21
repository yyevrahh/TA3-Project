#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iomanip>

using namespace std;

// count books in a specific genre
int getGenreCount(const string& code, const unordered_map<string, string>& centralIndexMap)
{
    int count = 0;
    for (auto const& [id, title] : centralIndexMap)
    {
        if (id.substr(0, 3) == code) count++;
    }
    return count;
}

// auto placement of book by availability
void getPlacement(int count, int& shelf, int& level)
{
    shelf = (count / 30) + 1;
    level = ((count % 30) / 10) + 1;
}

// member ID generation by append
string generateMemberID(int currentMemberCount)
{
    int nextID = currentMemberCount + 1;

    stringstream ss;
    ss << "MEM" << setfill('0') << setw(4) << nextID;
    
    return ss.str();
}