#include <iostream>

#include "trim.hpp"

int main()
{
    std::string testStr1("LAasdaE34fa adsoi 3 f3iufj3ol f jaso3 foiwje do3jm ifes fe ee            e              ");
    std::cout << testStr1 << "*\n";
    TrimRight(const_cast<char *>(testStr1.c_str()));
    std::cout << testStr1 << "*\n";

    std::string testStr2(readFileToStr("input.txt"));
    std::cout << testStr2 << "*\n";
    trimRight(testStr2);
    std::cout << testStr2 << "*\n";

    return EXIT_SUCCESS;
}
