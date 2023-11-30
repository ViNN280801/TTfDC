#include "settings.hpp"

std::string curtime(std::string const &format)
{
    std::chrono::system_clock::time_point tp{std::chrono::system_clock::now()};
    time_t tt{std::chrono::system_clock::to_time_t(tp)};
    struct tm *t{localtime(&tt)};
    std::stringstream ss;
    ss << std::put_time(t, format.c_str());
    return ss.str();
}
