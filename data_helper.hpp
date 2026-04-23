#ifndef DATA_HELPER_HPP
#define DATA_HELPER_HPP

#include <string>
#include <unordered_map>
#include "data_bundle.hpp"

using namespace std;

// Book ID and Placement Logic

/**
 * @brief checks the last index value of a specific genre
 * @param code the genre code
 * @param books the struct BookBundle
 * @return the number or the maxIndex (last) of the genre
*/
int getLastBookIndex(const string&, const BookBundle&);

/**
 * @brief calculates the placement of the book and directly modifies it
 * @param nextIndex the absolute next placement of the book
 * @param shelf address to the modifiable shelf value
 * @param level address to the modifiable level value
 */

void getPlacement(int, int&, int&);

/**
 * @brief generates the seven character unique ID for books
 * @param genre takes the genre of the book
 * @param books the struct BookBundle to add the record
 * @return the generated string of 7 characters book ID
*/
string generateBookID(const string&, const BookBundle&);

/**
 * @brief generates the seven char unique member ID
 * @param currentMemberCount for adding 1 to the count
 * @return the unique member ID
 */
string generateMemberID(int);

// Translation Helpers
/**
 * @brief translates provided id > code to equivalent genre
 * @param id to be substr and check for equivalence
 * @return the genre (e.g., "Fantasy") or "Unknown if not found"
 */

string translateCodeToGenre(string);
/**
 * @brief Translates a genre name into a 3-letter uppercase code.
 * @param genre The input string (e.g., "Science Fiction").
 * @return 3-letter code (e.g., "SCI") or "UNK" if not found.
 */
string translateGenreToCode(string);

// Output/UI Helpers

/**
 * @brief aligns text to the center of a specified width for table formatting.
 * @param text the string to be centered.
 * @param width the total width of the column.
 * @return string padded with spaces on both sides.
 */
string center(string text, int width);

/**
 * @brief Prints the column headers and a decorative divider for the book table.
 */
void printBookHeader();

/**
 * @brief prints a single row of book data with automatic truncation for long text.
 * @param id the formatted Book ID.
 * @param title the title of the book.
 * @param author the author of the book.
 * @param year the publication year.
 * @param publisher the publishing company.
 */
void printDataEntry(string id, string title, string author, int year, string publisher);

// Book CRUD Operations
/**
 * @brief UI to input book details and save them to the BookBundle.
 * @param books reference to the BookBundle where the new entry will be stored.
 */
void addBookEntry(BookBundle& books);

/**
 * @brief finds and displays a specific book's full details using its unique ID.
 * @param books reference to the BookBundle to search.
 */
void searchBookByID(BookBundle& books);

/**
 * @brief performs a partial string search across all book titles (case-insensitive).
 * @param books reference to the BookBundle to search.
 */
void searchBookByTitle(BookBundle& books);

/**
 * @brief filters and displays all books published in a specific year.
 * @param books reference to the BookBundle to search.
 */
void searchBookByYear(BookBundle& books);

/**
 * @brief performs a partial string search across all book authors (case-insensitive).
 * @param books reference to the BookBundle to search.
 */
void searchBookByAuthor(BookBundle& books);

/**
 * @brief performs a partial string search across all book publishers (case-insensitive).
 * @param books reference to the BookBundle to search.
 */
void searchBookByPublisher(BookBundle& books);

/**
 * @brief filters and displays all books belonging to a specific genre category.
 * @param books reference to the BookBundle to search.
 */
void searchByGenre(BookBundle& books);

/**
 * @brief looks through the central index and displays every book record.
 * @param books reference to the BookBundle to display.
 */
void showAllBooks(BookBundle& books);

/**
 * @brief UI to modify existing book details (Title, Year, Author, or Publisher).
 * @param books reference to the BookBundle containing the target record.
 */
void updateBook(BookBundle& books);

/**
 * @brief removes a book record and its associated borrow status from the database.
 * @param books reference to the BookBundle to remove the book from.
 * @param members reference to the MemberBundle to clear any active borrow records.
 */
void deleteBook(BookBundle& books, MemberBundle& members);

// Member CRUD Operations
/**
 * @brief creates a new entry for members
 * @param members reference to MemberBundle to insert the new entry
 */
void addMember(MemberBundle&);

/**
 * @brief performs a search if any member has the corresponding target ID
 * @param members reference to MemberBundle to check for the member with the requested ID
 */
void searchMemberByID(MemberBundle&);

/**
 * @brief performs a search if any member has the same or similar name
 * @param members refernce to MemberBundle to read and check for the members with the name
 */
void searchMemberByName(MemberBundle&);

/**
 * @brief updates the member name by ID only
 * @param members reference to MemberBundle to update the name of the one from the ID
 */
void updateMember(MemberBundle&);

/**
 * @brief deletes a member record from the map
 * @param members reference to MemberBundle to check and delete the record of the target member by ID
 */
void deleteMember(MemberBundle&);

// Borrow Operations
/**
 * @brief allows a member to borrow a book by ID
 * @param members reference to MemberBundle to check if member exists and pass it to borrows map
 * @param books reference to BookBundle to check if the book exists and then allow it to be borrowed
 */
void borrowABook(MemberBundle&, BookBundle&);

/**
 * @brief to delete or return the borrowed book from the record
 * @param members reference to MemberBundle to check and delete the record from borrows map
 */
void deleteMemberBorrowByBookID(MemberBundle&);
#endif