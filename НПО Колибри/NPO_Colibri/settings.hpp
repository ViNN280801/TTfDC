#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <chrono>
#include <concepts>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#define ERRMSG(desc) std::cerr << curtime() << ": Error: " << __PRETTY_FUNCTION__ << ": " << desc
#define LOGMSG(desc) std::clog << curtime() << ": Log: " << __PRETTY_FUNCTION__ << ": " << desc

/**
 * @brief Concept that checks if variable has output operator
 * @tparam a variable to check
 * @param os output stream
 */
template<typename T>
concept Printable = requires(T a, std::ostream &os) {
    {
        os << a
    } -> std::same_as<std::ostream &>;
};

/**
 * @brief Gets current time in specified format
 * @param format format to display time
 * @return Time as "std::string"
 */
extern std::string curtime(std::string const &format = "%d/%m/%Y %T");

/**
 * @brief Generates string with specified multiple args
 * @tparam args arguments of type that can be convert to string
 * @return String composed from all arguments
 */
template<typename... Args>
constexpr std::string gen_str(Args &&...args)
{
    std::ostringstream oss;
    (oss << ... << args);
    return oss.str();
}

#endif // SETTINGS_HPP
