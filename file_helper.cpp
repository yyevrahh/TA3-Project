#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// use for central index (initToCentralIndex), borrowed books, and library members.
void readAndAppend(string path, unordered_map<string, string>& targetMap)
{
    ifstream readFile(path);
    string line;

    if (!readFile)
    {
        cerr << "\e[1;31mError: Could not open.\e[0m" << path << endl;
        return;
    }

    while (getline(readFile, line)) 
    {
        if (line.length() < 8) continue; // skip empty

        string id = line.substr(0, 7);
        string content = line.substr(8);
        size_t secondCommaPos = content.find(',');

        if (secondCommaPos != string::npos)
        {
            targetMap.at(id) = content.substr(0, secondCommaPos);
        }
        else
        {
            targetMap.at(id) = content;
        }
    }

    readFile.close();
}

// programmed read and append for central index
void initToCentralIndex(unordered_map<string, string>& centralIndexMap)
{
    vector<string> genres = {"fantasy", "mystery", "romance", "science_fiction", "thriller"};
    for (const string& genre: genres)
    {
        readAndAppend("book_genres/" + genre + ".txt", centralIndexMap);
    }
}

// update the books under book_genres folder (id, title, author, year, publisher)
void updateGenresFile(unordered_map<string, string>& centralIndexMap, unordered_map<string, string>& authorMap, unordered_map<string, int>& yearMap, unordered_map<string, string>& publisherMap)
{
    ofstream fntFile("book_genres/fantasy.txt");
    ofstream mysFile("book_genres/mystery.txt");
    ofstream romFile("book_genres/romance.txt");
    ofstream sciFile("book_genres/science_fiction.txt");
    ofstream thrFile("book_genres/thriller.txt");

    for (auto const& [id, title] : centralIndexMap)
    {
        string genreCode = id.substr(0, 3);
        ofstream* targetFile = nullptr;

        if (genreCode == "FNT") targetFile = &fntFile;
        else if (genreCode == "MYS") targetFile = &mysFile;
        else if (genreCode == "ROM") targetFile = &romFile;
        else if (genreCode == "SCI") targetFile = &sciFile;
        else if (genreCode == "THR") targetFile = &thrFile;

        // check if all exists and ready
        if (targetFile && *targetFile) 
        {
            *targetFile << id << "," << title << "," << authorMap.at(id) << "," << yearMap.at(id) << "," << publisherMap.at(id) << endl;
        }
        else 
        {
            cerr << "\e[1;31mError: Invalid genre code or file error for ID: " << id << "\e0m" <<  endl;
        }
    }

    fntFile.close();
    mysFile.close();
    romFile.close();
    sciFile.close();
    thrFile.close();
}

// use to update key:value data from <string, string> maps
void updateFileByDataMapStr(string path, unordered_map<string, string>& dataMap)
{
    ofstream writeFile(path);
    string id, content;

    for (auto const& [id, content] : dataMap)
    {
        writeFile << id << "," << content << endl;
    }

    writeFile.close();
}

// use to update key:value data from <string, int> maps = yearMap
void updateFileByDataMapInt(string path, unordered_map<string, int>& dataMap)
{
    ofstream writeFile(path);

    string id;
    int year;

    for (auto const& [id, year] : dataMap)
    {
        writeFile << id << "," << year << endl;
    }

    writeFile.close();
}