#include <iterator>
#include <algorithm>

#include "trim.hpp"

std::string readFileToStr(std::string const &filename)
{
    std::fstream fin(filename);
    std::stringstream ss;
    ss << fin.rdbuf();
    return ss.str();
}

void TrimRight(char *s)
{
    size_t idx = strlen(s) - 1;
    while (isspace(s[idx]))
    {
        s[idx] = '\0';
        idx--;
    }
}

void trimRight(std::string &s)
{
    s.erase(std::find_if(std::rbegin(s), std::rend(s), [](char const &ch)
                         { return !isspace(ch); })
                .base(),
            s.end());
}
