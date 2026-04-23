/**
 * @file general_utils.cpp
 * @brief functions for utilities like int validation and UI activities
 */
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std; 

#include "general_utils.hpp"

int getValidInt(const string& prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        // keep the loop running for invalid vals
        if (cin.fail())
        {
            cin.clear(); // clear the error flag
            cin.ignore(1000, '\n'); // discard invalid char
            cout << "\t\e[1;31mInvalid input. Please enter a number.\e[0m" << endl;
        } 
        else
        {
            cin.ignore(1000, '\n'); // discard trailing chars
            return value;
        }
    }
}

/**
 * @note External Utility: Cross-platform "Press Any Key" implementation.
 * Sourced from community boilerplate to handle non-canonical terminal input 
 * for both Windows (conio.h) and Linux (termios.h) systems.
 */
void pressAnyKey() 
{
    cout << endl << endl;
    cout << "\nPress any key to continue..." << flush;

#ifdef _WIN32
    _getch();
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}

void cls()
{
    // Uses ANSI escape codes: \033[2J (clear screen) and \033[H (move cursor to home)
    cout << "\033[2J\033[H" << flush;
}

void wait(int ms)
{
    // thread > sleep > ms
    this_thread::sleep_for(chrono::milliseconds(ms));
}