#include <algorithm>
#include <cctype>
#include <iterator>

#include "menu.hpp"
#include "settings.hpp"

using namespace std::string_literals;

// Hint message
static const std::string hint{
    "\nAll blank fields will be filled automatically with the default values:\n"s
    + "a) \".*\\.txt\"\nb) All input files will not be removed\n"s
    + "c) Path to save output files is current directory\nd) Overwrite\n"s
    + "e) Start program with the timer\nf) 1 sec\ng) 1234567890\n"s
    + "Enter symbol from (a) to (g) or type \"end\" word to end your choice\n"s
    + "If you want to exit from the program, type \"exit\"\n"s
    + "Type \"hint\" or \"help\" to call this message again\n"s};

void printMenu()
{
    std::cout << "Configuration:\n"
                 "a) Mask of the input files\n"
                 "b) Necessary of the removing input files\n"
                 "c) Path to save result files\n"
                 "d) Actions when repeating the output file name: "
                 "overwriting or modification, for example, a counter to the file name\n"
                 "e) Work with a timer or starting program once\n"
                 "f) Polling frequency (only if at the step (e) your choice is a \"Timer\")\n"
                 "g) Value of 8 bytes to the binary modification\n";
}

char getChoiceFromMenu()
{
    std::string inputStr;
    while (true) {
        std::cout << "Your choice: ";
        std::getline(std::cin, inputStr);

        // Checking all cases
        if (inputStr == "exit"s) {
            std::cout << "Exiting...\n";
            std::exit(EXIT_SUCCESS);
        }

        if (inputStr == "end"s)
            return '#';

        if (inputStr == "hint"s or inputStr == "help"s) {
            std::cout << hint;
            return '*';
        }

        // Input string have to contain only letters from 'a' to 'g'
        if (inputStr.length() == 1ul && isalpha(inputStr.front()) && inputStr.front() >= 'a'
            && inputStr.front() <= 'g')
            break;
        else
            ERRMSG("incorrect input.\nYou need to input 1 letter from (a) to (g)\n");
    }
    return inputStr.front();
}

std::string getFileMask()
{
    std::string mask;
    std::cout << "Enter file mask: ";
    std::getline(std::cin, mask);
    return mask;
}

bool getFlag()
{
    std::string inputStr;
    std::cout << "Type \"false\" or \"true\": ";

    while (true) {
        std::getline(std::cin, inputStr);

        if (inputStr not_eq "false"s and inputStr not_eq "true"s)
            ERRMSG("invalid input. Try again: ");
        else
            break;
    }

    return (inputStr == "false"s) ? false : true;
}

std::string getOutPath()
{
    std::string sPath;
    std::cout << "Enter path: ";

    while (true) {
        std::getline(std::cin, sPath);

        // Checking is passed path really exists on the PC
        if (not std::filesystem::exists(sPath))
            ERRMSG("invalid path. Try again: ");
        else
            break;
    }

    return sPath;
}

Actions_To_Repeating_Files getAction()
{
    std::string inputStr;
    std::cout << "a) Overwrite\nb) Modification\n"
                 "c) Counter of files (Creates numbers for the repeating files at the end)\n"
                 "Just type a letter: from (a) to (c)\nEnter letter: ";

    while (true) {
        std::getline(std::cin, inputStr);

        if (inputStr == "a"s)
            return Actions_To_Repeating_Files::OVERWRITE;
        else if (inputStr == "b"s)
            return Actions_To_Repeating_Files::MODIFICATION;
        else if (inputStr == "c"s)
            return Actions_To_Repeating_Files::COUNTER_TO_FILE;
        else
            ERRMSG("invalid input. You need to type 1 letter from (a) to (c). Try again: ");
    }

    return Actions_To_Repeating_Files::OVERWRITE;
}

ulong getPollingFrequency()
{
    std::string inputStr;
    std::cout << "Enter polling frequency of a timer (in milliseconds): ";

    while (true) {
        std::getline(std::cin, inputStr);

        if (std::all_of(std::cbegin(inputStr), std::cend(inputStr), [](auto const &ch) {
                return isdigit(ch);
            }))
            break;
        else
            ERRMSG("invalid input. You need to write value in milliseconds (unsigned long value). "
                   "Try again: ");
    }

    return std::stoul(inputStr);
}

uint64_t get8ByteValue()
{
    std::string inputStr;
    std::cout << "Enter value of 8 bytes for binary file modification operation: ";

    while (true) {
        std::getline(std::cin, inputStr);

        if (std::all_of(std::cbegin(inputStr), std::cend(inputStr), [](auto const &ch) {
                return isdigit(ch);
            }))
            break;
        else
            ERRMSG("invalid input. You need to write value of 8 bytes (unsigned long value). "
                   "Try again: ");
    }

    return std::stoul(inputStr);
}

Configurations handleMenu()
{
    Configurations configurations;

    printMenu();
    std::cout << hint;
    char choice{0x00};

    while (choice != '#') {
        choice = getChoiceFromMenu();

        switch (choice) {
        case 'a':
            configurations.fileMask = getFileMask();
            break;
        case 'b':
            configurations.deleteInputFiles = getFlag();
            break;
        case 'c':
            configurations.outPath = getOutPath();
            break;
        case 'd':
            configurations.action = getAction();
            break;
        case 'e':
            configurations.startConfig = getFlag();
            break;
        case 'f':
            configurations.pollingFrequency = getPollingFrequency();
            break;
        case 'g':
            configurations.xor_value = get8ByteValue();
            break;
        default:
            break;
        }
    }

    return configurations;
}
