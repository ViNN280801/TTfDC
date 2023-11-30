#include <filesystem>
#include <fstream>
#include <utility>
#include <iostream>
#include <chrono>
#include <sstream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <iterator>

#include "../include/freverse.hpp"

std::string curtime(const char *format)
{
    std::chrono::system_clock::time_point tp{std::chrono::system_clock::now()};
    time_t tt{std::chrono::system_clock::to_time_t(tp)};
    struct tm *t{localtime(&tt)};
    std::stringstream ss;
    ss << std::put_time(t, format);
    return ss.str();
}

bool freverse::exists(std::string const &fname) const
{
    std::ifstream ifs(fname.c_str());
    return ifs.good();
}

void freverse::create_file(std::string const &fname) const
{
    // Creating file with specified name
    std::ofstream ofs(fname);

    // Check if file was created successfully
    if (ofs.bad())
    {
        std::cerr << ERRMSG("Can't create file \'") << fname << "\'\n";
        return;
    }

#ifdef LOG
    std::clog << LOGMSG("Successfully created file \'") << fname << "\'\n";
#endif // !LOG

    ofs.close();
}

void freverse::check_existance_create(std::string const &fname) const
{
    if (not exists(fname))
        create_file(fname);
}

void freverse::change_fname(std::string const &newfname)
{
    if (not exists(m_fname))
        return;

    std::error_code ec;
    std::filesystem::rename(m_fname, newfname, ec);

    if (ec)
    {
        std::cerr << ERRMSG("Can't rename file \'" + m_fname + "\' to \'" + newfname + "\'. Error code: ") << ec << '\n';
        return;
    }

#ifdef LOG
    std::clog << LOGMSG("Successfully renamed file \'") << m_fname << "\' to \'" << newfname << "\'\n";
#endif // !LOG

    m_fname = newfname;
}

freverse::freverse() : m_fname(kdefault_fname) { check_existance_create(m_fname); }

freverse::freverse(std::string const &newfname) : m_fname(newfname) { check_existance_create(m_fname); }

freverse::freverse(std::string &&newfname) : m_fname(std::move(newfname)) { check_existance_create(m_fname); }

freverse::freverse(freverse const &rhs) : m_fname(rhs.m_fname) { change_fname(rhs.m_fname); }

freverse::freverse(freverse &&lhs) noexcept : m_fname(std::move(lhs.m_fname)) { change_fname(lhs.m_fname); }

freverse &freverse::operator=(freverse const &rhs)
{
    // Check self-assigning
    if (this == &rhs)
        return *this;

    change_fname(rhs.m_fname);
    m_fname = rhs.m_fname;

    return *this;
}

freverse &freverse::operator=(freverse &&lhs) noexcept
{
    if (this == &lhs)
        return *this;

    change_fname(lhs.m_fname);
    m_fname = std::exchange(lhs.m_fname, nullptr);

    return *this;
}

freverse::~freverse() { m_fname.clear(); }

const std::string freverse::get_filename() const { return m_fname; }

void freverse::rename(std::string const &newfname)
{
    change_fname(newfname);
    m_fname = newfname;
}

void freverse::rename(std::string &&newfname)
{
    change_fname(newfname);
    m_fname = std::move(newfname);
}

void freverse::reverse(std::string const &inf, std::string const &outf) const
{
    std::ifstream ifs(inf, std::ios_base::binary);

    if (ifs.bad())
    {
        std::cerr << ERRMSG("Can't open file \'" + inf + "\' in the binary mode. Exiting...");
        return;
    }

    std::ofstream ofs(outf, std::ios_base::binary);

    if (ofs.bad())
    {
        std::cerr << ERRMSG("Can't open file \'" + outf + "\' in the binary mode. Exiting...");
        return;
    }

    // Read content from the inout file to the vector of bytes using input stream buffer iterator
    std::vector<std::string> words;
    std::string word;

    while (ifs >> word)
    {
        // Erasing all commas
        std::erase_if(word, [](auto const &ch)
                      { return ch == ','; });
        word += ", ";
        words.push_back(word);
    }

    // Closing input file stream
    ifs.close();

    // Reversing buffer
    std::ranges::reverse(words);

    // Writing reversed data to the output file
    for (auto &w : words)
    {
        // Erasing last ", " symbols
        if (w == *(std::cend(words) - 1))
            w.erase(w.length() - 2, 2);
        ofs << w;
    }
    ofs << '\n';

    // Closing output file stream
    ofs.close();

#ifdef LOG
    std::clog << LOGMSG("Successfully reversed bytes from input file \'" + inf + "\' to output file \'" + outf + "\'") << '\n';
#endif
}
