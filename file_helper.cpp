#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "data_bundle.hpp"

using namespace std;
// run these functions for both initializing and exiting

void initAllData(BookBundle& books) {
    vector<string> genres = {"fantasy", "mystery", "romance", "science_fiction", "thriller"};
    
    for (const string& genre : genres) {
        ifstream file("book_genres/" + genre + ".txt");
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string id, title, author, yearStr, publisher;

            if (getline(ss, id, ',') &&
                getline(ss, title, ',') &&
                getline(ss, author, ',') &&
                getline(ss, yearStr, ',') &&
                getline(ss, publisher)) 
            {
                books.centralIndex[id] = title;
                books.authors[id] = author;
                books.years[id] = stoi(yearStr);
                books.publishers[id] = publisher;
            }
        }
        file.close();
    }
}

// update the books under book_genres folder (id, title, author, year, publisher)
void updateGenresFile(BookBundle& books)
{
    ofstream fntFile("book_genres/fantasy.txt");
    ofstream mysFile("book_genres/mystery.txt");
    ofstream romFile("book_genres/romance.txt");
    ofstream sciFile("book_genres/science_fiction.txt");
    ofstream thrFile("book_genres/thriller.txt");

    for (auto const& [id, title] : books.centralIndex)
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
            *targetFile << id << "," << title << "," << books.authors.at(id) << "," << books.years.at(id) << "," << books.publishers.at(id) << endl;
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

// use to update key:value data from <string, int> maps = years
void updateFileByDataMapYears(string path, const BookBundle& books)
{
    ofstream writeFile(path);

    string id;
    int year;

    for (auto const& [id, year] : books.years)
    {
        writeFile << id << "," << year << endl;
    }

    writeFile.close();
}