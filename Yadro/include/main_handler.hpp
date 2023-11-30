#ifndef MAIN_HANDLER_HPP
#define MAIN_HANDLER_HPP

#include <iostream>
#include <cstring> // for func 'strcmp()' that returns 0 when strings are eq

#include "../include/tapesorter.hpp"
#include "../include/tape.hpp"

#define PRINT_USAGE_MSG std::cout << "Usage: " << argv[0] << " <input_tape> <output_tape> [restricted size in bytes]\n";

#define PRINT_ERROR_MSG_AND_EXIT                                                                                       \
    {                                                                                                                  \
        std::string unknownCommand;                                                                                    \
        for (int i = 0; i < argc; i++)                                                                                 \
            unknownCommand += argv[i] + std::string(" ");                                                              \
        std::cout << "Error: Command: \"" << unknownCommand << "\" is unknown command\n"                               \
                  << "Run \"" << argv[0] << "\" with any of help agruments: \"--h\"; \"-h\"; \"--help\"; \"-help\"\n"; \
        exit(EXIT_FAILURE);                                                                                            \
    }

/**
 * @brief Checks if 2nd passed argument is helper flag
 * @param argv main arguments
 * @return "true" if 2nd passed argument is helper flag
 */
constexpr bool isHelpMode(const char **argv)
{
    return strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--h") == 0 ||
           strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "--help") == 0;
}

void handleMain(int argc, const char **argv)
{
    switch (argc)
    {
    case 2:
    {
        if (isHelpMode(argv))
            PRINT_USAGE_MSG
        else
            PRINT_ERROR_MSG_AND_EXIT
        break;
    }
    case 3:
    {
        // Creating input tape with 1000 random elements
        Tape t(argv[1], 1'000);
        t.generate_random_tape(1'000);

        // Sorting input tape to output tape using temporary tapes
        TapeSorter ts;
        ts.sort(argv[1], 1'000, argv[2], 1'000 * sizeof(int));
        break;
    }
    case 4:
    {
        Tape t(argv[1], 1'000);
        t.generate_random_tape(1'000);

        // Sorting input tape to output tape using temporary tapes with restricted size (in bytes)
        TapeSorter ts;
        ts.sort(argv[1], 1'000, argv[2], std::stoul(std::string(argv[3])));
        break;
    }
    default:
        PRINT_ERROR_MSG_AND_EXIT
    }
}

#endif // !MAIN_HANDLER_HPP
