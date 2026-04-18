#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void readAndAppend(string path, unordered_map<string, string>& targetArr)
{
    // use for central index (initToCentralIndex), borrowed books, and library members.
    ifstream readFile(path);
    string id, content;

    if (!readFile) {
        cerr << "Error: Could not open " << path << endl;
        return;
    }

    while(getline(readFile, id, ',') && getline(readFile, content))
    {
        targetArr[id] = content;
    }

    readFile.close();
}

void initToCentralIndex(unordered_map<string, string>& centralIndexMap)
{
    vector<string> genres = {"fantasy", "mystery", "romance", "science_fiction", "thriller"};
    for (const string& genre: genres)
    {
        readAndAppend("book_genres/" + genre + ".txt", centralIndexMap);
    }
}

void updateGenresFile(unordered_map<string, string>& centralIndexMap)
{
    unordered_map<string, string> genresCodes = 
    {
        {"fantasy", "FNT"},
        {"mystery", "MYS"},
        {"romance", "ROM"},
        {"science_fiction", "SCI"},
        {"thriller", "THR"}
    };

    for (auto const& [genre, code] : genresCodes)
    {
        ofstream writeFile("book_genres/" + genre + ".txt");

        for (auto const& [id, title] : centralIndexMap)
        {
            if (id.find(code) == 0)
            {
                writeFile << id << "," << title << endl;
            }
        }
    }
    
    writeFile.close();
}

void updateFileByArrData(string path, unordered_map<string, string>& dataArr)
{
    ofstream writeFile(path);
    string id, content;

    for (auto const& [id, content] : dataArr)
    {
        writeFile << id << "," << content << endl;
    }

    writeFile.close();
}
