/**
 * @file enu_procs.cpp
 * @brief Menu processes handler and dispatcher
 * Includes functions for navigating through operations/methods from @file data_helper.cpp
 */
#include <iostream>
#include "menu_procs.hpp"
#include "data_bundle.hpp"
#include "data_helper.hpp"
#include "general_utils.hpp"

using namespace std;

void bookMenu(BookBundle& books, MemberBundle& members)
{
    while (true)
    {
        cls();
        cout << "\t Book Management \n"
             << "\t[1] Add Book\n"
             << "\t[2] Search Book\n"
             << "\t[3] Update Book\n"
             << "\t[4] Delete Book\n"
             << "\t[5] Show all Books\n"
             << "\t[0] Back to Main Menu\n";
        int choice = getValidInt("\tChoice: ");
        // user to move back up the menu hierarchy
        if (choice == 0) break;
        cls();
        // selection to the appropriate data_helper function
        if (choice == 1) addBookEntry(books);
        else if (choice == 2) bookSearchMenu(books);
        else if (choice == 3) updateBook(books);
        else if (choice == 4) deleteBook(books, members);
        else if (choice == 5) showAllBooks(books);
    }
}

void memberMenu(BookBundle& books, MemberBundle& members)
{
    while (true) {
        cls();
        cout << "\t Member & Borrow Management \n"
             << "\t[1] Register Member\n"
             << "\t[2] Search Member\n"
             << "\t[3] Update Member\n"
             << "\t[4] Delete Member\n"
             << "\t[5] Borrow a Book\n"
             << "\t[6] Return a Book\n"
             << "\t[0] Back to Main Menu\n";
        int choice = getValidInt("\tChoice: ");
        cls();
        if (choice == 0) break;

        if (choice == 1) addMember(members);
        else if (choice == 2)
        {
            int sChoice = getValidInt("\t[1] By ID | [2] By Name: ");
            if (sChoice == 1) searchMemberByID(members);
            else if (sChoice == 2) searchMemberByName(members);
        }
        else if (choice == 3) updateMember(members);
        else if (choice == 4) deleteMember(members);
        else if (choice == 5) borrowABook(members, books);
        else if (choice == 6) deleteMemberBorrowByBookID(members);
    }
}

void bookSearchMenu(BookBundle& books)
{
    while (true)
    {
        cls();
        cout << "\t Search Book Database \n"
             << "\t[1] Search by ID\n"
             << "\t[2] Search by Title\n"
             << "\t[3] Search by Author\n"
             << "\t[4] Search by Year\n"
             << "\t[5] Search by Publisher\n"
             << "\t[6] Search by Genre\n"
             << "\t[0] Back\n";
        
        int choice = getValidInt("\tChoice: ");
        if (choice == 0) break;
        cls();
        if (choice == 1) searchBookByID(books);
        else if (choice == 2) searchBookByTitle(books);
        else if (choice == 3) searchBookByAuthor(books);
        else if (choice == 4) searchBookByYear(books);
        else if (choice == 5) searchBookByPublisher(books);
        else if (choice == 6) searchByGenre(books);
    }
}