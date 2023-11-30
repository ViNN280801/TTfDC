#include <iostream>
#include <cinttypes>

#include "dictionary.hpp"

int main()
{
    // Provided some test case
    Dictionary<uint32_t, int> dictionary;

    // Test 1: Inserting and recieving values
    dictionary.set(10u, 1);
    dictionary.set(37u, 11);

    int value1{dictionary.get(10u)}, value2{dictionary.get(37u)};

    if (value1 == 10u && value2 == 37u)
        std::cout << "Test 1: passed\n";
    else
        std::cout << "Test 1: failed\n";

    // Test 2: Check existence
    bool exists1{dictionary.is_set(37u)}, exists2{dictionary.is_set(53u)};

    if (exists1 && !exists2)
        std::cout << "Test 2: passed\n";
    else
        std::cout << "Test 2: failed\n";

    // Test 3: Try to retrieve a non-existing key and handle the exception
    try
    {
        [[maybe_unused]] int value3{dictionary.get(104u)};
        std::cout << "Test 3: Exception handling failed (key found)\n";
    }
    catch (DictionaryKeyNotFoundException<uint32_t> const &ex)
    {
        std::cout << "Test 3: Exception handling passed (key not found)\n";
    }
    catch (...)
    {
        std::cout << "Test 3: Caught unexpected exception\n";
    }

    return EXIT_SUCCESS;
}