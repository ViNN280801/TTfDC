gcc -g -c main.cpp -lstdc++ -std=c++20 -Wall -Wpedantic -Wextra -o main.o
gcc main.o -lstdc++ -std=c++20 -o main
rm main.o
./main
