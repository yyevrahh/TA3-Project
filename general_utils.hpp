#ifndef GENERAL_UTILS_HPP
#define GENERAL_UTILS_HPP

#include <iostream>

using namespace std;

/**
 * @brief ensures the user enters a valid integer, handling non-numeric input errors.
 * @param prompt the message displayed to the user.
 * @return verified integer value.
 */
int getValidInt(const string& prompt);

/**
 * @brief cross-platform utility that pauses execution until any key is pressed.
 * @note this implementation uses non-canonical mode to bypass the 'Enter' key requirement.
 */
void pressAnyKey();

/**
 * @brief clears the terminal screen and resets the cursor position to the top-left.
 */
void cls();

/**
 * @brief pauses the program for a specific duration.
 * @param ms milliseconds to wait.
 */
void wait(int ms);

#endif