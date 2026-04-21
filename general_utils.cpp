#include <iostream>
#include <string>

using namespace std;

int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\e[1;31mInvalid input. Please enter a number.\e[0m" << endl;
        } 
        else {
            cin.ignore(1000, '\n');
            return value;
        }
    }
}

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

void pressAnyKey() 
{
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
