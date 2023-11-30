#ifndef FUNCTIONALITY_HPP
#define FUNCTIONALITY_HPP

#include <cinttypes>
#include <filesystem>
#include <string>
#include <vector>

#include "menu.hpp"

/**
 * @brief Puts all content from the file to string obj
 * @param file path to a file
 * @return All content from a file 'file' as a "std::string"
 */
std::string readFileToStr(char const *file);

/**
 * @brief Modifies file with XOR op
 * @param in input filename
 * @param out output filename
 * @param xor_value value to do XOR op on each byte in a file
 */
void modifyFile(char const *in, char const *out, uint64_t xor_value);

/**
 * @brief Collect all filenames with specified mask into a vector
 * @param path path where to search
 * @param mask file mask
 * @return Filenames with specified mask in the vector
 */
std::vector<std::string> getFilenamesByMask(
    std::filesystem::path const &path = std::filesystem::current_path(),
    std::string const &mask = ".*\\.txt$");

void modifyFileHandler(std::vector<std::string> const &files, Configurations config);

#endif // FUNCTIONALITY_HPP
