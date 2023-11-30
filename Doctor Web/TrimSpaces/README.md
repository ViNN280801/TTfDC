# Младший программист C++ / Junior C++ Developer (Windows, UNIX)

## Description

This is a test temporaly repo, that contains answer to 1 task, the condition of which is following:

### Rus

Напишите функцию, которая обрезает пробелы в конце переданной ей строки. Функция должна быть написана в расчёте на работу с очень длинными строками с очень большим количеством пробелов, оптимизирована по количеству обращений к памяти. <b>Сигнатура:</b> void TrimRight(char \*s);

### Eng

Write a function that truncates the spaces at the end of the string passed to it. The function should be written to work with very long strings with a very large number of spaces, optimized for the number of memory accesses. <b>Signature:</b> void trimRight(char \*s);

## Compiling

There is file [autoconf.sh](https://github.com/ViNN280801/Test/blob/main/autoconf.sh) that will compiles this project for you automatically. But if you want to do this by yourself, below are presented commands to do that:

### GNU GCC

```console
gcc -g -c trim.cpp -lstdc++ -std=c++17 -Wall -Wpedantic -Wextra -o trim.o
gcc -g -c main.cpp -lstdc++ -std=c++17 -Wall -Wpedantic -Wextra -o main.o
gcc main.o trim.o -lstdc++ -std=c++17 -o main
rm trim.o main.o
./main
```

### CMake

```console
cmake .
cmake --build .
./main
```
