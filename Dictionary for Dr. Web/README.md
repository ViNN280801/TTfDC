# Dictionary for Dr. Web

## Task descripton

It is necessary to implement a container class that implements the dictionary interface and is able to throw an exception that implements the not_found_exception interface.
When developing, it is allowed to use STL. In addition, the internal implementation is not limited by anything.

```cpp
template<class Key, class Value>
class dictionary
{
public:
    virtual ~dictionary() = default;

    virtual const Value& get(const Key& key) const = 0;
    virtual void set(const Key& key, const Value& value) = 0;
    virtual bool is_set(const Key& key) const = 0;
};

template<class Key>
class not_found_exception : public std::exception
{
public:
    virtual const Key& get_key() const noexcept = 0;
};
```

To do this task I used some concepts that are applied to Key and Value (dictionary.hpp):

```cpp
static_assert(is_copyable_v<Key>, "Key has to be copyable");
static_assert(is_equality_comparable_v<Key>, "Key has to be equality comparable");
static_assert(is_hashable_v<Key>, "Key has to be hashable");
static_assert(is_copy_constructible_v<Value>, "Value has to be copy constructible");
```

Also, I changed names of the interfaces and implemented it by very simple way - just used STL dictionary container within the '<b>Dictionary<Key, Value></b>' template class - "<b>std::unordered_map<></b>".
And I provided some tests task in the <b>main.cpp</b> source file to check functionality of this class.

## Compiling

There is file <b>autocompile.sh</b> that will compiles this project for you automatically. But if you want to do this by yourself, below are presented commands to do that:

### GNU GCC

There is code from the <b>autocompile.sh</b> file.

```bash
gcc -g -c main.cpp -lstdc++ -std=c++20 -Wall -Wpedantic -Wextra -o main.o
gcc main.o -lstdc++ -std=c++20 -o main
rm main.o
./main
```

After creating this script you need to change mode to executive file with the following command:

```bash
chmod +x autocompile.sh
./autocompile.sh
```

### CMake

```bash
cmake .
cmake --build .
./main
```

or

```bash
cmake .
make
./main
```

## Memory check

Using [valgrind](https://valgrind.org) tool for check of any memory leaks or errors in a program:

```bash
valgrind ./<Your executive file>
```

If you want to use valgrind with full check and with lists of errors, run following command:

```bash
valgrind --leak-check=full --show-leak-kinds=all -s ./<Your executive file>
```

Output:

```console
==26473== Memcheck, a memory error detector
==26473== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==26473== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==26473== Command: ./main
==26473==
Test 1: failed
Test 2: passed
Test 3: Exception handling passed (key not found)
==26473==
==26473== HEAP SUMMARY:
==26473==     in use at exit: 0 bytes in 0 blocks
==26473==   total heap usage: 6 allocs, 6 frees, 75,032 bytes allocated
==26473==
==26473== All heap blocks were freed -- no leaks are possible
==26473==
==26473== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

How you can see, I have still reachable bytes (16,768 bytes in 7 blocks), it is not the issue of the program. These blocks seems to be related to GLib library, which is commonly used in C/C++ programs. Valgrind didn't report about any memory leaks, so, it's no problems in a functionality.It's a normal behavior of many C/C++ programs that use libraries like GLib.

If you want to redirect valgrind checking to a file, use command below:

```bash
valgrind --leak-check=yes -s --log-file="memory.log" ./<Your executive file>
```
