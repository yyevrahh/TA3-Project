#ifndef MENU_PROCS_HPP
#define MENU_PROCS_HPP
#include "data_bundle.hpp"

/**
 * @brief displays the Book sub-menu and handles navigation for book operations.
 * allows access to adding, searching, updating, and deleting book records.
 * @param books reference to the BookBundle for data operations.
 * @param members reference to the MemberBundle for cross-referencing borrow status.
 */
void bookMenu(BookBundle& books, MemberBundle& members);

/**
 * @brief shows Member & Borrowing sub-menu for user and transaction management.
 * @param books Reference to the BookBundle for book availability checks.
 * @param members Reference to the MemberBundle for data operations.
 */
void memberMenu(BookBundle& books, MemberBundle& members);

/**
 * @brief displays specialized search options to filter the book database by various attributes.
 * provides a secondary navigation layer for ID, Title, Author, Year, Publisher, and Genre searches.
 * @param books reference to the BookBundle to be queried.
 */
void bookSearchMenu(BookBundle& books);

#endif