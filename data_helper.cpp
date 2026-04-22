#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <sstream>
#include "general_utils.hpp"
#include "data_bundle.hpp"
#include "data_helper.hpp"

// TODO: COMMENTSSSS
// TODO: general unknown genres!!!!!!!!
// TODO: keep hpp updated!!
// TODO: generateBookID ID collision
// general data entry output is: ID TITLE YEAR AUTHOR GENRE PUBLISHER
// no title maps!!! it is in books.centralIndex

using namespace std;

// count books in a specific genre
int getGenreCount(const string& code, const BookBundle& books)
{
    int count = 0;
    for (auto const& [id, title] : books.centralIndex)
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

string generateBookID(const string& genre, const BookBundle& books)
{
    string genreCode = translateGenreToCode(genre);
    transform(genreCode.begin(), genreCode.end(), genreCode.begin(), ::toupper);

    if (genreCode.length() < 3)
    {
        cerr << "\e[1;31mError: Genre name too short.\e[0m" << endl;
        pressAnyKey();
        return "";
    }

    int count = getGenreCount(genreCode, books);
    int shelf, level;
    getPlacement(count, shelf, level);

    stringstream ss;
    ss << genreCode << setfill('0') << setw(2) << shelf << setw(2) << level;

    return ss.str();
}

string translateCodeToGenre(string id)
{
    string genreCode = id.substr(0, 3);
    if (genreCode == "FNT") return "Fantasy"; // can be refactored to FAN, but I won't
    else if (genreCode == "MYS") return "Mystery";
    else if (genreCode == "ROM") return "Romance";
    else if (genreCode == "SCI") return "Science-fiction";
    else if (genreCode == "THR") return "Thriller";

    return "UNKNOWN";
}

string translateGenreToCode(string genre)
{
    transform(genre.begin(), genre.end(), genre.begin(), ::tolower);

    if (genre == "fantasy") return "FNT"; // can be refactored to FAN, but I won't
    else if (genre == "mystery") return "MYS";
    else if (genre == "romance") return "ROM";
    else if (genre == "science fiction" || genre == "sci-fi") return "SCI";
    else if (genre == "thriller") return "THR";

    return "UNK";
}

string center(string text, int width) 
{
    if (text.length() >= width) return text;
    int padding = width - text.length();
    int leftPad = padding / 2;
    int rightPad = padding - leftPad;
    return string(leftPad, ' ') + text + string(rightPad, ' ');
}

void printBookHeader()
{
    // Widths (Define these once here to keep them consistent)
    int wID = 12, wTitle = 35, wYear = 10, wAuthor = 25, wGenre = 20, wPub = 25;

    cout << center("ID", wID)
         << center("TITLE", wTitle)
         << center("YEAR", wYear)
         << center("AUTHOR", wAuthor)
         << center("GENRE", wGenre)
         << center("PUBLISHER", wPub) << endl;

    cout << string(wID + wTitle + wYear + wAuthor + wGenre + wPub, '-') << endl;
}

void printDataEntry(string id, string title, string author, int year, string publisher)
{
    int wID = 12, wTitle = 35, wYear = 10, wAuthor = 25, wGenre = 20;
    string genre = translateCodeToGenre(id);
    if (title.length() > 32)
    {
        title = title.substr(0, 29) + "...";
    }
    if (author.length() > 22)
    {
        author = author.substr(0, 19) + "...";
    }
    if (publisher.length() > 22)
    {
        publisher = publisher.substr(0,19) + "...";
    }
    cout << left 
         << "  " << setw(wID - 2)     << id 
         << "  " << setw(wTitle - 2)  << title 
         << "   " << setw(wYear - 2)   << year 
         << "  " << setw(wAuthor - 2) << author 
         << "  " << setw(wGenre - 2)  << genre 
         << publisher << endl;
}

void addBookEntry(BookBundle& books)
{
    cout << "\tAdd a new Book" << endl;
    string genre, id;
    do 
    {
        cout << "\tGenre: ";
        getline(cin >> ws, genre);

        id = generateBookID(genre, books);
    } while (id.substr(0, 3) == "UNK");
    if (id == "") return;

    string title, author, publisher;
    int year;
    cout << "\tTitle: ";
    getline(cin >> ws, title);

    year = getValidInt("\tYear: ");

    cout << "\tAuthor: ";
    getline(cin >> ws, author);

    cout << "\tPublisher: ";
    getline(cin >> ws, publisher);

    books.centralIndex[id] = title;
    books.years[id] = year;
    books.authors[id] = author;
    books.publishers[id] = publisher;

    cout << "\tEntry \e[1;32madded\e[0m";
    for (int i = 0; i < 3; i++)
    {
        wait(300);
        cout << "." << flush;
    }

    cls();
    printBookHeader();
    printDataEntry(id, title, author, year, publisher);
    pressAnyKey();
    cls();
}

void searchBookByID(BookBundle& books)
{
    while (true)
    {
        cls();
        cout << "\tSearch for a Book" << endl;
        cout << "\tID: ";
        string id;
        cin >> id;

        if (id.length() < 7 || id.length() > 7)
        {
            cout << "\t\t\e[1;31mInvalid ID. Try again";
            for (int i = 0; i < 3; i++)
            {
                wait(300);
                cout << "." << flush;
            }
            cout << "\e[0m";
            continue;
        }

        if (books.centralIndex.find(id) == books.centralIndex.end())
        {
            cout << "\t\t\e[1;31mBook not found.\e[0m";
            wait(1500);
            cls();
            break;
        }

        cls();
        printBookHeader();
        printDataEntry(id, books.centralIndex[id], books.authors[id], books.years[id], books.publishers[id]);
        pressAnyKey();
        cls();
        break;
    }
}

void searchBookByTitle(BookBundle& books)
{
    cls();
    cout << "\tSearch for Book(s)" << endl;
    cout << "\tTitle: ";
    string titleInput;
    getline(cin >> ws, titleInput);

    transform(titleInput.begin(), titleInput.end(), titleInput.begin(), ::toupper);

    cls();
    int results = 0;
    printBookHeader();
    for (auto const& [id, title] : books.centralIndex)
    {
        string temp = title;
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        if (temp.find(titleInput) != string::npos)
        {
            results++;
            printDataEntry(id, title, books.authors[id], books.years[id], books.publishers[id]);
        }
    }

    if (results == 0)
    {
        cls();
        cout << "\t\t\e[1;31mNo matching books for: \e[1;37m" << titleInput << "\e[1;31m found.\e[0m";
        wait(1500);
        cls();
    }
    else 
    {
        cout << "\n\tFound \e[1;32m" << results << "\e[0m matching entry(ies)." << endl;
        pressAnyKey();
        cls();
    }
}

void searchBookByYear(BookBundle& books)
{
    cls();
    cout << "\tSearch for Book(s) by Year" << endl;
    int yearInput = getValidInt("\tYear: ");

    cls();
    int results = 0;
    printBookHeader();
    for (auto const& [id, year] : books.years)
    {
        if (year == yearInput)
        {
            results++; 
            printDataEntry(id, books.centralIndex[id], books.authors[id], year, books.publishers[id]);
        }
    }

    if (results == 0)
    {
        cls();
        cout << "\t\t\e[1;31mNo matching entries for year: \e[1;37m" << yearInput << "\e[1;31m found.\e[0m";
        wait(1500);
        cls();
    }
    else 
    {
        cout << "\n\tFound \e[1;32m" << results << "\e[0m matching entry(ies)." << endl;
        pressAnyKey();
        cls();
    }
}

void searchBookByAuthor(BookBundle& books)
{
    cls();
    cout << "\tSearch for Book(s)" << endl;
    cout << "\tAuthor: ";
    string authorInput;
    getline(cin >> ws, authorInput);

    transform(authorInput.begin(), authorInput.end(), authorInput.begin(), ::toupper);

    cls();
    int results = 0;
    printBookHeader();
    for (auto const& [id, author] : books.authors)
    {
        string temp = author;
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        if (temp.find(authorInput) != string::npos)
        {
            results++;
            printDataEntry(id, books.centralIndex[id], author, books.years[id], books.publishers[id]);
        }
    }

    if (results == 0)
    {
        cls();
        cout << "\t\t\e[1;31mNo matching books from: \e[1;37m" << authorInput << "\e[1;31m found.\e[0m";
        wait(1500);
        cls();
    }
    else 
    {
        cout << "\n\tFound \e[1;32m" << results << "\e[0m matching entry(ies)." << endl;
        pressAnyKey();
        cls();
    }
}

void searchBookByPublisher(BookBundle& books)
{
    cls();
    cout << "\tSearch for Book(s)" << endl;
    cout << "\tAuthor: ";
    string publisherInput;
    getline(cin >> ws, publisherInput);

    transform(publisherInput.begin(), publisherInput.end(), publisherInput.begin(), ::toupper);

    cls();
    int results = 0;
    printBookHeader();
    for (auto const& [id, publisher] : books.publishers)
    {
        string temp = publisher;
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        if (temp.find(publisherInput) != string::npos)
        {
            results++;
            printDataEntry(id, books.centralIndex[id], books.authors[id], books.years[id], publisher);
        }
    }

    if (results == 0)
    {
        cls();
        cout << "\t\t\e[1;31mNo matching books from: \e[1;37m" << publisherInput << "\e[1;31m found.\e[0m";
        wait(1500);
        cls();
    }
    else 
    {
        pressAnyKey();
        cls();
    }
}

void updateBook(BookBundle& books)
{
    while (true)
    {
        cls();
        cout << "\t\e[1;34mUpdate\e[0m a Book" << endl;
        cout << "\tID: ";
        string id;
        cin >> id;

        if (books.centralIndex.find(id) == books.centralIndex.end())
        {
            cout << "\t\t\e[1;31mBook not found.\e[0m";
            wait(1500);
            break;
        }

        cls();
        printBookHeader();
        printDataEntry(id, books.centralIndex[id], books.authors[id], books.years[id], books.publishers[id]);

        cout << "\n\t[1] Title\n\t[2] Year\n\t[3] Author\n\t[4] Publisher\n\t[0] Cancel" << endl;
        int choice = getValidInt("\tChoice: ");

        if (choice < 0 || choice >= 5) continue;
        if (choice == 0) return;
        if (choice == 2)
        {
            books.years[id] = getValidInt("\tNew Year: ");
        } 
        else
        {
            string p = choice == 1 ? "Title" : choice == 3 ? "Author" : "Publisher";
            cout << "\tNew " << p << ": ", getline(cin >> ws, (choice == 1 ? books.centralIndex[id] : choice == 3 ? books.authors[id] : books.publishers[id]));
        }
        cout << "\n\t\e[1;32mRecord updated!\e[0m" << endl;
        pressAnyKey();
        break;
    }
}

void searchByGenre(BookBundle& books)
{
    cls();
    cout << "\tSearch by Genre\n\t(Fantasy, Mystery, Romance, Sci-Fi, Thriller)\n";
    string genreInput;
    cout << "\tEnter Genre: ";
    getline(cin >> ws, genreInput);

    string code = translateGenreToCode(genreInput);
    if (code == "UNK")
    {
        cout << "\t\e[1;31mInvalid Genre.\e[0m" << endl;
        wait(1000);
        return;
    }

    cls();
    int results = 0;
    printBookHeader();
    for (auto const& [id, title] : books.centralIndex)
    {
        if (id.substr(0, 3) == code)
        {
            results++;
            printDataEntry(id, title, books.authors[id], books.years[id], books.publishers[id]);
        }
    }

    if (results == 0) cout << "\t\t\e[1;31mNo books found in this genre.\e[0m" << endl;
    else cout << "\n\tFound \e[1;32m" << results << "\e[0m books." << endl;
    
    pressAnyKey();
}

void showAllBooks(BookBundle& books)
{
    cls();
    if (books.centralIndex.empty())
    {
        cout << "\t\e[1;31mLibrary is empty.\e[0m" << endl;
        wait(1500);
        return;
    }

    printBookHeader();
    for (auto const& [id, title] : books.centralIndex)
    {
        printDataEntry(id, title, books.authors[id], books.years[id], books.publishers[id]);
    }
    cout << "\n\tTotal Books: " << books.centralIndex.size() << endl;
    pressAnyKey();
}

void deleteBook(BookBundle& books, MemberBundle& members)
{
    while (true)
    {
        cls();
        cout << "\t\e[1;31mDelete\e[0m a Book" << endl;
        cout << "\tID: ";
        string id;
        cin >> id;

        if (id.length() < 7 || id.length() > 7)
        {
            cout << "\t\t\e[1;31mInvalid ID. Try again";
            for (int i = 0; i < 3; i++)
            {
                wait(300);
                cout << "." << flush;
            }
            cout << "\e[0m";
            continue;
        }

        if (books.centralIndex.find(id) == books.centralIndex.end())
        {
            cout << "\t\t\e[1;31mBook not found.\e[0m";
            wait(1500);
            cls();
            break;
        }

        cls();
        printBookHeader();
        printDataEntry(id, books.centralIndex[id], books.authors[id], books.years[id], books.publishers[id]);
        int choice;
        if (members.borrows.count(id) > 0) 
        {
            cout << "\t\tThis book is currently borrowed.." << endl;
            choice = getValidInt("\t\t\e[1;31mDelete\e[1;37m " + books.centralIndex[id] + "\e[0m anyway? [0] Cancel \t [1] Proceed\n\tChoice: ");
        }
        else
        {
            choice = getValidInt("\t\t\e[1;31mDelete\e[1;37m " + books.centralIndex[id] + "\e[0m? [0] Cancel \t [1] Proceed\n\tChoice: ");
        }

        if (choice == 0) break;
        else if (choice == 1)
        {
            books.centralIndex.erase(id);
            books.authors.erase(id);
            books.years.erase(id);
            books.publishers.erase(id);
            members.borrows.erase(id);
        }
        pressAnyKey();
        cls();
        break;
    }
}

void addMember(MemberBundle& members)
{
    cls();
    cout << "\tRegister New Member" << endl;
    
    string name;
    cout << "\tEnter Full Name: ";
    getline(cin >> ws, name);

    string id = generateMemberID(members.nextId++);

    members.users[id] = name;

    cout << "\n\t\e[1;32mSuccess!\e[0m Member ID: \e[1;33m" << id << "\e[0m" << endl;
    pressAnyKey();
    cls();
}

void searchMemberByID(MemberBundle& members)
{
    cls();
    cout << "\tSearch Member Info" << endl;
    string id;
    cout << "\tID: ";
    cin >> id;

    auto it = members.users.find(id);
    if (it == members.users.end())
    {
        cout << "\t\e[1;31mError: Member ID not found.\e[0m" << endl;
        wait(1500);
        return;
    }

    cout << "\e[1;32mMember ID:" << id << " found!\e[0m" << endl;
    cout << "\tMember Name: " << it->second << endl;    
    pressAnyKey();
}

void searchMemberByName(MemberBundle& members)
{
    cls();
    cout << "\tSearch Member Info" << endl;
    string nameInput;
    cout << "\tFull name: ";
    getline(cin >> ws, nameInput);

    cls();
    int results = 0;

    cout << left << setw(15) << "ID" << setw(30) << "NAME" << endl;
    cout << string(45, '-') << endl;

    for (auto const& [id, name] : members.users)
    {
        string temp = name;
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        string searchUpper = nameInput;
        transform(searchUpper.begin(), searchUpper.end(), searchUpper.begin(), ::toupper);

        if (temp.find(searchUpper) != string::npos)
        {
            results++;
            cout << left << setw(15) << id << setw(30) << name << endl;
        }
    }

    if (results == 0)
    {
        cls();
        cout << "\t\t\e[1;31mNo matching name(s): \e[1;37m" << nameInput << "\e[1;31m found.\e[0m";
        wait(1500);
        cls();
    }
    else 
    {
        pressAnyKey();
        cls();
    }
}

void updateMember(MemberBundle& members)
{
    cls();
    cout << "\tUpdate Member Info" << endl;
    string id;
    cout << "\tID: ";
    cin >> id;

    auto it = members.users.find(id);
    if (it == members.users.end())
    {
        cout << "\t\e[1;31mError: Member ID not found.\e[0m" << endl;
        wait(1500);
        return;
    }

    cout << "\tCurrent Name: " << it->second << endl;
    string newName;
    cout << "\tEnter New Name: ";
    getline(cin >> ws, newName);

    int confirm = getValidInt("\tSave changes? [1] Yes | [0] Cancel: ");
    if (confirm == 1)
    {
        it->second = newName;
        cout << "\t\e[1;32mUpdate successful.\e[0m" << endl;
    }
    else
    {
        cout << "\t\e[1;33mUpdate cancelled.\e[0m" << endl;
    }
    pressAnyKey();
}

void deleteMember(MemberBundle& members)
{
    cls();
    cout << "\tDelete Member Account" << endl;
    string id;
    cout << "\tID: ";
    cin >> id;

    if (members.users.find(id) == members.users.end())
    {
        cout << "\t\e[1;31mError: ID not found.\e[0m" << endl;
        wait(1500);
        return;
    }

    bool hasBorrowedBooks = false;
    for (auto const& [bookID, memberID] : members.borrows)
    {
        if (memberID == id)
        {
            hasBorrowedBooks = true;
            break;
        }
    }

    if (hasBorrowedBooks)
    {
        cout << "\t\e[1;31mProcess Denied:\e[0m Member has unreturned books." << endl;
    }
    else
    {
        int choice = getValidInt("\tAre you sure you want to delete this member? [1] Yes | [0] No: ");
        if (choice == 1)
        {
            members.users.erase(id);
            cout << "\t\e[1;32mMember record removed.\e[0m" << endl;
        }
    }
    pressAnyKey();
}


void borrowABook(MemberBundle& members, BookBundle& books)
{
    cls();
    cout << "\tBorrow a Book" << endl;
    string bookID, memID;
    cout << "\tBook ID: ";
    cin >> bookID;
    cout << "\tMember ID: ";
    cin >> memID;

    transform(bookID.begin(), bookID.end(), bookID.begin(), ::toupper);
    transform(memID.begin(), memID.end(), memID.begin(), ::toupper);

    if (books.centralIndex.find(bookID) == books.centralIndex.end())
    {
        cout << "\t\e[1;31mError: Book ID not found.\e[0m" << endl;
        wait(1500);
        return;
    }
    else if (members.users.find(memID) == members.users.end())
    {
        cout << "\t\e[1;31mError: Member ID not found.\e[0m" << endl;
        wait(1500);
        return;
    }
    else if (members.borrows.count(bookID))
    {
        cout << "\t\e[1;31mError: Book is already borrowed by " << members.borrows[bookID] << ".\e[0m" << endl;
        wait(1500);
        return;
    }
    else
    {
        int choice = getValidInt("\tBorrow " + books.centralIndex[bookID] + "? [1] Yes | [0] No: ");
        if (choice == 1)
        {
            members.borrows[bookID] = memID;
            cout << memID << "\n\n\t\e[1;32msuccessfully borrowed \e[0m" << books.centralIndex[bookID] << endl;
        }
    }
    pressAnyKey();
}

void deleteMemberBorrowByBookID(MemberBundle& members)
{
    cls();
    cout << "\tReturn / Delete Borrow Record" << endl;
    string bID;
    cout << "\tEnter Book ID to Return: ";
    cin >> bID;
    transform(bID.begin(), bID.end(), bID.begin(), ::toupper);

    auto it = members.borrows.find(bID);
    if (it == members.borrows.end())
    {
        cout << "\t\e[1;31mError: No active borrow record for this book.\e[0m" << endl;
    }
    else
    {
        cout << "\tBorrowed by: " << members.users[it->second] << " (" << it->second << ")" << endl;
        if (getValidInt("\tMark as returned? [1] Yes | [0] No: ") == 1)
        {
            members.borrows.erase(it);
            cout << "\t\e[1;32mBook returned successfully.\e[0m" << endl;
        }
    }
    pressAnyKey();
}