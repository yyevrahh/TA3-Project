#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <general_utils.hpp>

// TODO: book search, delete, update funcs
// TODO: member CRUD funcs

// general data entry output is: ID TITLE YEAR AUTHOR GENRE PUBLISHER
// no title maps!!! it is on centralIndexMap

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

// auto placement of book
void getPlacement(int count, int& shelf, int& level)
{
    shelf = (count / 30) + 1;
    level = ((count % 30) / 10) + 1;
}

// member ID generation by append with filler
string generateMemberID(int currentMemberCount)
{
    int nextID = currentMemberCount + 1;

    stringstream ss;
    ss << "MEM" << setfill('0') << setw(4) << nextID;
    
    return ss.str();
}

string generateBookID(const string& genre, unordered_map<string, string>& centralIndexMap)
{
    string genreCode = translateGenreToCode(genre);
    transform(genreCode.begin(), genreCode.end(), genreCode.begin(), ::toupper);

    if (genreCode.length() < 3)
    {
        cerr << "\e[1;31mError: Genre name too short.\e[0m" << endl;
        pressAnyKey();
        return "";
    }

    int count = getGenreCount(genreCode, centralIndexMap);
    int shelf, level;
    getPlacement(count, shelf, level);

    stringstream ss;
    ss << genreCode << setfill('0') << setw(2) << shelf << setw(2) << level;

    return ss.str();
}

string translateCodeToGenre(string id)
{
    string genreCode = id.substr(0, 3);
    if (genreCode == "FNT") return "Fantasy";
    else if (genreCode == "MYS") return "Mystery";
    else if (genreCode == "ROM") return "Romance";
    else if (genreCode == "SCI") return "Science-fiction";
    else if (genreCode == "THR") return "Thriller";

    return "UNNKOWN";
}

string translateGenreToCode(string genre)
{
    transform(genre.begin(), genre.end(), genre.begin(), ::tolower);

    if (genre == "fantasy") return "FNT";
    else if (genre == "mystery") return "MYS";
    else if (genre == "romance") return "ROM";
    else if (genre == "science-fiction") return "SCI";
    else if (genre == "thriller") return "THR";

    return "UNK";
}

void printDataEntry(string id, string title, string author, int year, string publisher)
{
    string genre = translateCodeToGenre(id);
    cout << left << setw(10) << id 
         << setw(25) << title 
         << setw(6)  << year 
         << setw(20) << author 
         << setw(10) << genre 
         << publisher << endl;
}

void addBookEntry(
    unordered_map<string, string>& centralIndexMap, unordered_map<string, string>& authorMap, 
    unordered_map<string, int>& yearMap, unordered_map<string, string>& publisherMap
)
{
    string genre;
    cout << "\tBook Genre: ";
    cin >> genre;

    string id = generateBookID(genre, centralIndexMap);
    if (id == "") return;

    string title, author, publisher;
    int year;
    cout << "\tBook title: ";
    getline(cin >> ws, title);

    year = getValidInt("\tYear: ");

    cout << "\tBook author: ";
    getline(cin >> ws, author);

    cout << "\tBook publisher: ";
    getline(cin >> ws, publisher);

    centralIndexMap[id] = title;
    yearMap[id] = year;
    authorMap[id] = author;
    publisherMap[id] = publisher;

    cout << "\tEntry \e[1;32madded.\e[0m" << endl;
    printDataEntry(id, title, author, year, publisher);
}