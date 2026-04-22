#ifndef DATA_HELPER_HPP
#define DATA_HELPER_HPP

#include <string>
#include <unordered_map>
#include "data_bundle.hpp"

using namespace std;

// Book ID and Placement Logic
int getGenreCount(const string&, const BookBundle&);
void getPlacement(int, int&, int&);
string generateBookID(const string&, const BookBundle&);

// Member Logic
string generateMemberID(int);

// Translation Helpers
string translateCodeToGenre(string);
string translateGenreToCode(string);

// Output/UI Helpers
string center(string, int);
void printBookHeader();
void printDataEntry(string, string, string, int, string);

// Book CRUD Operations
void addBookEntry(BookBundle&);
void searchBookByID(BookBundle&);
void searchBookByTitle(BookBundle&);
void searchBookByYear(BookBundle&);
void searchBookByAuthor(BookBundle&);
void searchBookByPublisher(BookBundle&);
void searchByGenre(BookBundle&);
void showAllBooks(BookBundle&);
void updateBook(BookBundle&);
void deleteBook(BookBundle&, MemberBundle&); // ID only!

// Member CRUD Operations
void addMember(MemberBundle&);
void searchMemberByID(MemberBundle&);
void searchMemberByName(MemberBundle&);
void updateMember(MemberBundle&);
void deleteMember(MemberBundle&);

// Book Operations
void borrowABook(MemberBundle&, BookBundle&);
void deleteMemberBorrowByBookID(MemberBundle&);
#endif