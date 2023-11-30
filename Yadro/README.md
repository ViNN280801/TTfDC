# Yadro TATLIN Data Services

## Task description

### Eng

A Tape type data storage device (Tape) is designed for sequential writing and reading of data. The read/write magnetic head is stationary during reading and writing, and the tape has the ability to move in both directions. Recording and reading of information is possible in the cell of the tape on which the magnetic head is currently located. Moving the tape is a time–consuming operation – the tape is not intended for random access.

There is an input tape of length N (where N is large) containing elements of type integer (2^32). There is an output tape of the same length. It is necessary to write the ascending elements from the input tape to the output tape. There is a limitation on the use of RAM – no more than M bytes (M can be < N, i.e. it will not be possible to load all data from the tape into RAM). To implement the algorithm, you can use a reasonable number of time years, i.e. tapes on which you can store some temporary information necessary during the operation of the algorithm.

It is necessary to create a C++ project compiled into a console application that implements an algorithm for sorting data from the input tape to the output. You need to do the following:

- Define an interface for working with a tape type device.
- Write a class that implements this interface and emulates working with the tape using a regular file. It should be possible to configure (without recompilation – for example, through an external configuration file that will be read at the start of the application) delays in writing/reading an element from the tape, rewinding the tape, and shifting the tape by one position.
- Files of time years can be saved to the tmp directory.
- Write a class that implements an algorithm for sorting data from the input tape to the output.
- The console application must accept the input name of the input and output files and sort them.
- It is advisable to write unit tests.

### Рус

Устройство хранения данных типа лента (Tape) предназначено для последовательной записи и чтения данных. Считывающая/записывающая магнитная головка неподвижна во время чтения и записи, а лента имеет возможность двигаться в обоих направлениях. Запись и чтение информации возможны в ячейку ленты, на которой в данный момент находится магнитная головка. Перемещения ленты – затратная по времени операция – лента не предназначена для произвольного доступа.

Имеется входная лента длины N (где N – велико), содержащая элементы типа integer (2^32). Имеется выходная лента такой же длины. Необходимо записать в выходную ленту отсортированные по возрастанию элементы с входной ленты. Есть ограничение по использованию оперативной памяти – не более M байт (M может быть < N, т.е. загрузить все данные с ленты в оперативную память не получится). Для реализации алгоритма можно использовать разумное количество временных лент, т.е. лент, на которых можно хранить какую-то временную информацию, необходимую в процессе работы алгоритма.

Необходимо создать проект С++, компилируемый в консольное приложение, которое реализует алгоритм сортировки данных с входной ленты на выходную. Необходимо сделать следующее:

- Определить интерфейс для работы с устройством типа лента.
- Написать класс, реализующий этот интерфейс и эмулирующий работу с лентой посредством обычного файла. Должно быть возможно сконфигурировать (без перекомпиляции – например, через внешний конфигурационный файл, который будет прочитан на старте приложения) задержки по записи/чтению элемента с ленты, перемотки ленты, и сдвига ленты на одну позицию.
- Файлы временных лент можно сохранять в директорию tmp.
- Написать класс, реализующий алгоритм сортировки данных с входной ленты на выходную.
- Консольное приложение должно принимать на вход имя входного и выходного файлов и производить сортировку.
- Желательно написать юнит-тесты.

## Compile

Two ways to compile are represented here:

1. Compile with bash script 'autocompile.sh'.
2. Compile with CMake.

### Compiling with script

```console
./autocompile.sh
```

### Compiling with CMake

```console
cmake .
cmake --build .
```

Result:

```console
<loveit@fedora Yadro>$ cmake .
-- The CXX compiler identification is GNU 12.3.1
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.4s)
-- Generating done (0.0s)
-- Build files have been written to: /home/vladislavsemykin/Documents/prog/Others/Yadro
<loveit@fedora Yadro>$ cmake --build .
[ 25%] Building CXX object CMakeFiles/main.dir/src/tape.cpp.o
[ 50%] Building CXX object CMakeFiles/main.dir/src/tapesorter.cpp.o
[ 75%] Building CXX object CMakeFiles/main.dir/src/main.cpp.o
[100%] Linking CXX executable main
[100%] Built target main
<loveit@fedora Yadro>$
```

## Description of the project

This is a console application which is sorting elements from the input tape to the output using several (or one: depends on restricted size of temporary tapes in bytes) temporary temporary tapes.
Interface 'ITape' in 'tape.hpp' tries to repeat work of STL "std::vector" but it works with files as a tape with integer values on it. Interface is implemented by class 'Tape'. There is used C++20 standard ["std::ranges"](https://en.cppreference.com/w/cpp/ranges) and all classes in this project written with [Rule of five](https://en.cppreference.com/w/cpp/language/rule_of_three), it means that all of these classes supports default constructor, constructors with parameters, copy-assignment operator, move-assignment operator and destructor.
Implemented class to sort tape which calls 'TapeSorter'. Main method in this class is 'sort' that have 2 signatures:

1. 'sort()' that copying objects;
2. 'sort()' that support move semantics:

```cpp
void sort(std::string const &srctape, size_t count, std::string const &desttape, size_t restrictbytes) const;
void sort(std::string &&srctape, size_t count, std::string &&desttape, size_t restrictbytes) const;
```

This class creates directory 'tmp' that will contains temporary tape files with elements from input tapes. These temporary tapes used to sort all elements from the input tape to output tape.
In 'main_handler.hpp' declared and defined functions that handles user's input.

## Examples

### Example 1

#### With no restricted size

```console
<loveit@fedora Yadro>$ ./main
Error: Command: "./main " is unknown command
Run "./main" with any of help agruments: "--h"; "-h"; "--help"; "-help"
<loveit@fedora Yadro>$ ./main --help
Usage: ./main <input_tape> <output_tape> [restricted size in bytes]
<loveit@fedora Yadro>$ ls
autocompile.sh  CMakeLists.txt  img  include  main  README.md  src
<loveit@fedora Yadro>$ ./main in out
```

<img src=img/1.png>
<img src=img/2.png>
<img src=img/3.png>

```console
<loveit@fedora Yadro>$ ls tmp/
14-06-2023_17:13:07-000
```

In base case restricted size of temporary tapes isn't specified. Restricted size is equals size of input tape, thus programm creates one temporary tape ('1'000 \* sizeof(int)'):

```cpp
// Creating input tape with 1000 random elements
Tape t(argv[1], 1'000);
t.generate_random_tape(1'000);

// Sorting input tape to output tape using temporary tapes
TapeSorter ts;
ts.sort(argv[1], 1'000, argv[2], 1'000 * sizeof(int));
break;
```

### Example 2

#### With restricted size

```console
<loveit@fedora Yadro>$ ./main -h
Usage: ./main <input_tape> <output_tape> [restricted size in bytes]
<loveit@fedora Yadro>$ ./main in out 251
<loveit@fedora Yadro>$ ls
autocompile.sh  img  include  out        src
CMakeLists.txt  in   main     README.md  tmp
<loveit@fedora Yadro>$ ls tmp/
14-06-2023_17:54:41-000  14-06-2023_17:55:09-005  14-06-2023_17:55:09-011
14-06-2023_17:55:09-000  14-06-2023_17:55:09-006  14-06-2023_17:55:09-012
14-06-2023_17:55:09-001  14-06-2023_17:55:09-007  14-06-2023_17:55:09-013
14-06-2023_17:55:09-002  14-06-2023_17:55:09-008  14-06-2023_17:55:09-014
14-06-2023_17:55:09-003  14-06-2023_17:55:09-009  14-06-2023_17:55:09-015
14-06-2023_17:55:09-004  14-06-2023_17:55:09-010
<loveit@fedora Yadro>$ ls -l tmp/
total 68
-rw-r--r--. 1 vladislavsemykin vladislavsemykin 3874 Jun 14 17:54 14-06-2023_17:54:41-000
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  176 Jun 14 17:55 14-06-2023_17:55:09-000
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  216 Jun 14 17:55 14-06-2023_17:55:09-001
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-002
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-003
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-004
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-005
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-006
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-007
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-008
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-009
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-010
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-011
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-012
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-013
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-014
-rw-r--r--. 1 vladislavsemykin vladislavsemykin  248 Jun 14 17:55 14-06-2023_17:55:09-015
<loveit@fedora Yadro>$
```

How we can see all files (5-th column of result of "ls -l" command) do not exceed 251 bytes which we specified in line:

```console
<loveit@fedora Yadro>$ ./main in out 251
```

<img src=img/4.png>
<img src=img/5.png>
<img src=img/6.png>
<img src=img/7.png>
<img src=img/8.png>

How sorter sorts input tape by splitting it into the several temporary tapes:

```cpp
Tape t(argv[1], 1'000);
t.generate_random_tape(1'000);

// Sorting input tape to output tape using temporary tapes with restricted size (in bytes)
TapeSorter ts;
ts.sort(argv[1], 1'000, argv[2], std::stoul(std::string(argv[3])));
break;
```

Inside 'sort()' method in pseudocode:

```
func sort:
[
    -> Checking size
    -> Init in and out tape objs
    -> Get copy of the input tape
    -> Creating dir
    -> Iterating by temp tapes
        [
            -> Generating name of 'i'-th temp tape
            -> Init tape obj with limited size
            -> Filling temp tape while copy of 'i'-th input tape is not empty
            [
                -> Get minimal element from the input tape and add it to temporary tape
                -> Erasing this min element from the copy of input tape
            ]
        ]
    -> Adding to the end of the output tape all elements from the each temporary tape
]
```

## Dockerfile

### Build Dockerfile

```console
sudo systemctl start docker
sudo docker login
sudo docker pull alpine:latest
sudo docker build -t console_app .
```

Output:

```console
Authenticating with existing credentials...
WARNING! Your password will be stored unencrypted in /root/.docker/config.json.
Configure a credential helper to remove this warning. See
https://docs.docker.com/engine/reference/commandline/login/#credentials-store

Login Succeeded
latest: Pulling from library/alpine
8a49fdb3b6a5: Pull complete
Digest: sha256:02bb6f428431fbc2809c5d1b41eab5a68350194fb508869a33cb1af4444c9b11
Status: Downloaded newer image for alpine:latest
docker.io/library/alpine:latest
[+] Building 98.6s (12/12) FINISHED
 => [internal] load .dockerignore                                                                                                 0.3s
 => => transferring context: 2B                                                                                                   0.0s
 => [internal] load build definition from Dockerfile                                                                              0.3s
 => => transferring dockerfile: 312B                                                                                              0.0s
 => [internal] load metadata for docker.io/library/alpine:latest                                                                  0.0s
 => [console_app 1/5] FROM docker.io/library/alpine                                                                               0.1s
 => [internal] load build context                                                                                                 0.4s
 => => transferring context: 1.80MB                                                                                               0.1s
 => [console_app 2/5] RUN apk add build-base cmake make                                                                          90.3s
 => [console_app 3/5] WORKDIR /app                                                                                                0.4s
 => [console_app 4/5] COPY . .                                                                                                    0.3s
 => [console_app 5/5] RUN cmake . &&     cmake --build .                                                                          6.0s
 => [stage-1 2/3] COPY --from=console_app /app /app                                                                               0.2s
 => [stage-1 3/3] WORKDIR /app                                                                                                    0.2s
 => exporting to image                                                                                                            0.2s
 => => exporting layers                                                                                                           0.2s
 => => writing image sha256:1365410958b90b15c445fad87ce0732f1893475fbc669587833460e47370f70b                                      0.0s
 => => naming to docker.io/library/console_app                                                                                    0.0s
<loveit@fedora Yadro>$
```

Command to run docker container:

```console
sudo docker container run console_app:latest
```

## Memory leaks

Using [valgrind](https://valgrind.org) tool to check of any memory leaks or errors in a program:

```console
valgrind ./main in out
```

Result:

```console
<loveit@fedora Yadro>$ valgrind ./main in out
==122841== Memcheck, a memory error detector
==122841== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==122841== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==122841== Command: ./main in out
==122841==
==122841==
==122841== HEAP SUMMARY:
==122841==     in use at exit: 0 bytes in 0 blocks
==122841==   total heap usage: 73,034 allocs, 73,034 frees, 55,330,120 bytes allocated
==122841==
==122841== All heap blocks were freed -- no leaks are possible
==122841==
==122841== For lists of detected and suppressed errors, rerun with: -s
==122841== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

If you want to use valgrind with full check and with lists of errors, run following command:

```console
valgrind --leak-check=yes -s ./main in out 251
```

Result:

```console
<loveit@fedora Yadro>$ valgrind --leak-check=yes -s ./main in out 251
==122981== Memcheck, a memory error detector
==122981== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==122981== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==122981== Command: ./main in out 251
==122981==
==122981==
==122981== HEAP SUMMARY:
==122981==     in use at exit: 0 bytes in 0 blocks
==122981==   total heap usage: 69,545 allocs, 69,545 frees, 50,644,936 bytes allocated
==122981==
==122981== All heap blocks were freed -- no leaks are possible
==122981==
==122981== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

If you want to redirect valgrind checking to a file, use command below:

```console
valgrind --leak-check=yes -s --log-file="memory.log" ./main in out 251
```
