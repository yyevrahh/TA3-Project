#ifndef FILE_HELPER_HPP
#define FILE_HELPER_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "data_bundle.hpp"

using namespace std;

//TODO: refactor update.

/**
 * @brief loads all library data from text files into the memory bundles.
 * reads genres from the /book_genres/ folder and members from members.txt.
 * @param books reference to the BookBundle to populate.
 * @param members reference to the MemberBundle to populate.
 */
void initAllData(BookBundle&, MemberBundle&);

/**
 * @brief updates by writing to all the files under /book_genres/ folder
 * @param books refernce to BookBundle to get the data from the maps
 */
void updateGenresFile(BookBundle&);

/**
 * @brief used for non members of the Book bundle and outside of the /book_genres/ folder
 * @param path the file path to be written to
 * @param dataMap the unordered_map to get the data from
 */
void updateFileByDataMapStr(string, unordered_map<string, string>&);

/**
 * @brief syncs the memory bundles back to the physical text files.
 * @param books ref to the BookBundle containing the latest data.
 * @param members reference to the MemberBundle containing the latest data.
 * @return true if save was successful, false otherwise.
 */
bool saveAllData(BookBundle&, MemberBundle&);

/**
 * @brief S=scans a file to find the highest numerical ID suffix.
 * used during startup to synchronize the nextId counter for members.
 * @param filename the path to the file to scan (e.g., "members.txt").
 * @return the highest ID integer found.
 */
int getNext(string);

#endif
