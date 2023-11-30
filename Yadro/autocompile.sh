#!/bin/bash

# Compiling source code files of main project
gcc -c src/tape.cpp -lstdc++ -std=c++20 -Wall -Wpedantic -Wextra -o tape.o
gcc -c src/tapesorter.cpp -lstdc++ -std=c++20 -Wall -Wpedantic -Wextra -o tapesorter.o
gcc -c src/main.cpp -lstdc++ -std=c++20 -Wall -Wpedantic -Wextra -o main.o

# Building project from compiled object files
gcc tape.o tapesorter.o main.o -lstdc++ -std=c++20 -Wall -Wpedantic -Wextra -o main

# Removing all object files as these are unnecessary
rm *.o
