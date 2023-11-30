#ifndef MENU_HPP
#define MENU_HPP

#include <cinttypes>
#include <filesystem>
#include <string>

/// @brief Enumeration that describes behaviour of the program when it has repeating files
enum Actions_To_Repeating_Files { OVERWRITE = 0, MODIFICATION = 1, COUNTER_TO_FILE = 2 };

/// @brief The Configurations struct that contains all configuration settings
struct Configurations
{
    std::string fileMask{".*\\.txt$"}; // Mask of input files, e.g. .txt, testFile.bin
    bool deleteInputFiles{false};      // Setting whether to delete input files or not
    std::string outPath{std::filesystem::current_path()}; // Path to save the result files
    Actions_To_Repeating_Files action{OVERWRITE}; // Actions when repeating the output file name:
        // overwriting or modification, for example, a
        // counter to the file name
    bool startConfig{true};        // Work on timer ("true") or starting once ("false")
    ulong pollingFrequency{1000l}; // Polling frequency of a timer (in milliseconds)
    uint64_t xor_value{1234567890ul}; // Value of 8 bytes for binary file modification operation
};

/// @brief Prints menu to terminal
extern void printMenu();

/**
 * @brief Getting user's choice in the menu
 * @return Char that corresponds to certain configuration
 */
extern char getChoiceFromMenu();

/**
 * @brief Handler for menu
 * @return Struct that contains all configurations that user chose
 */
extern Configurations handleMenu();

/**
 * @brief Gets file mask
 * @return File mask
 */
extern std::string getFileMask();

/**
 * @brief Gets flag
 * @return "true" or "false"
 */
extern bool getFlag();

/**
 * @brief Gets path
 * @return Path of the output files
 */
extern std::string getOutPath();

/**
 * @brief Gets action from enum
 * @return Action that will be applied to repeating files
 */
extern Actions_To_Repeating_Files getAction();

/**
 * @brief Gets polling frequency in seconds
 * @return Polling frequency
 */
extern ulong getPollingFrequency();

/**
 * @brief Gets value of 8 bytes for binary file modification operation
 * @return Value of 8 bytes for binary file modification
 */
extern uint64_t get8ByteValue();

#endif // MENU_HPP
