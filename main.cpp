#include <iostream>
#include <string>
#include "data_bundle.hpp"
#include "data_helper.hpp"
#include "file_helper.hpp"
#include "general_utils.hpp"
#include "menu_procs.hpp"

using namespace std;

int main() 
{
    // Init data bundles
    BookBundle books;
    MemberBundle members;
    initAllData(books, members); 
    
    // Sync member ID next generation
    members.nextId = getNext("members.txt");

    cls();
    cout << "\n\t\e[1;31m=====================================" << endl;
    cout << "\t\e[1;37m      TUP LIBRARY SYSTEM v1.0" << endl;
    cout << "\t\e[1;31m=====================================\e[0m" << endl;
    wait(2000);

    // manu nav operations
    while (true) 
    {
        cls();
        cout << "\t\e[1;37mMain Menu\e[0m" << endl;
        cout << "\t---------------------------" << endl;
        cout << "\t[1] Book Management" << endl;
        cout << "\t[2] Member & Borrowing" << endl;
        cout << "\t[0] \e[1;31mSave and Exit\e[0m" << endl;
        cout << "\t---------------------------" << endl;
        
        int choice = getValidInt("\tChoice: ");

        cls();
        if (choice == 0) 
        {
            cls();
            cout << "\t\e[1;33mSecuring data...\e[0m" << endl;
            
            // data permanence upon proper exit
            if (saveAllData(books, members))
            {
                cout << "\t\e[1;32mDatabase saved successfully.\e[0m" << endl;
            } 
            else
            {
                cout << "\t\e[1;31mError saving data! Check file permissions.\e[0m" << endl;
            }
            
            cout << "\tExiting system. Goodbye!" << endl;
            wait(1500);
            break;
        }

        if (choice == 1) 
        {
            bookMenu(books, members);
        } 
        else if (choice == 2) 
        {
            memberMenu(books, members);
        }
        else 
        {
            cout << "\t\e[1;31mInvalid option.\e[0m" << endl;
            wait(800);
        }
    }
    return 0;
}