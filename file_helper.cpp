#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "data_bundle.hpp"
#include "file_helper.hpp"

using namespace std;
// run these functions for both initializing and exiting pls

void initAllData(BookBundle& books, MemberBundle& members) {
    vector<string> genres = {"fantasy", "mystery", "romance", "science_fiction", "thriller"};

    for (const string& genre : genres)
    {
        ifstream file("book_genres/" + genre + ".txt");
        if (!file.is_open()) continue;

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, title, author, yearStr, publisher;

            if (getline(ss, id, ',') && getline(ss, title, ',') &&
                getline(ss, author, ',') && getline(ss, yearStr, ',') &&
                getline(ss, publisher)) 
            {
                books.centralIndex[id] = title;
                books.authors[id] = author;
                books.years[id] = stoi(yearStr);
                books.publishers[id] = publisher;
            }
        }
    }

    ifstream memFile("members.txt");
    string line;
    while (getline(memFile, line))
    {
        stringstream ss(line);
        string id, name;
        if (getline(ss, id, ',') && getline(ss, name))
        {
            members.users[id] = name;
        }
    }

    ifstream borrowsFile("borrowed_books.txt");
    while (getline(borrowsFile, line))
    {
        stringstream ss(line);
        string bookID, memID;
        if (getline(ss, bookID, ',') && getline(ss, memID))
        {
            members.borrows[bookID] = memID; 
        }
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
            *targetFile << id << "," << title << "," << books.authors[id] << "," << books.years[id] << "," << books.publishers[id] << endl;
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

int getNext(string filename)
{
    ifstream file(filename);
    if (!file.is_open()) return 0;

    int maxID = 0;
    string line;

    while (getline(file, line))
    {
        if (line.empty()) continue;
        try
        {
            size_t firstDelim = line.find(',');
            string idPart = line.substr(0, firstDelim);
            int currentID = stoi(idPart.substr(3));
            if (currentID > maxID) maxID = currentID;
        }
        catch (...) { continue; }
    }
    return maxID;
}

bool saveAllData(BookBundle& books, MemberBundle& members)
{
    try
    {
        updateGenresFile(books);
        updateFileByDataMapStr("members.txt", members.users);
        updateFileByDataMapStr("borrowed_books.txt", members.borrows);

        return true;
    }
    catch (...)
    {
        return false;
    }
}