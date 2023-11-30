#ifndef MAIN_HANDLER_HPP
#define MAIN_HANDLER_HPP

#include <iostream>
#include <cstring>

#include "freverse.hpp"

#define PRINT_USAGE_MSG std::cout << "Usage: " << argv[0] << " <input file> <output file>\n"

void mainHandler(int argc, char **argv)
{
    if (argc != 3)
    {
        PRINT_USAGE_MSG;
        return;
    }

    freverse frev(argv[1]);
    frev.reverse(argv[1], argv[2]);
}

#endif // !MAIN_HANDLER_HPP
