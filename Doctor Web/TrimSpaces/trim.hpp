#ifndef TRIM_HPP
#define TRIM_HPP

#include <cstring>
#include <string>
#include <sstream>
#include <fstream>

/// @brief Reads file content to an 'std::string' object
/// @param filename name of a certain file from which do you want to copy content to a string
/// @return All content from a file 'filename' as a "std::string"
std::string readFileToStr(std::string const &filename);

/// @brief Erases whitespaces from the end of the string 's' representes as ptr on a "char" (C-style method)
/// @param s string where you want to erase trailing whitespaces
void TrimRight(char *s);

/// @brief Erases whitespaces from the end of the string 's' representes as ptr on a "char" (C++ version)
/// @param s string where you want to erase trailing whitespaces
void trimRight(std::string &s);

#endif // !TRIM_HPP