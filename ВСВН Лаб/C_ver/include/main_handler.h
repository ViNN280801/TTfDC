#ifndef MAIN_HANDLER_H
#define MAIN_HANDLER_H

#include <stdio.h>
#include <string.h>

#include "freverse.h"

#define PRINT_USAGE_MSG printf("Usage: %s <input file> <output file>\n", argv[0]);

void mainHandler(int argc, char **argv)
{
    if (argc != 3)
    {
        PRINT_USAGE_MSG;
        return;
    }

    reverse(argv[1], argv[2]);
}

#endif // !MAIN_HANDLER_H
