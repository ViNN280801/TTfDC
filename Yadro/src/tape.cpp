#include <filesystem>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
#include <ranges>
#include <chrono>  // To get current datetime
#include <ctime>   // To get current datetime
#include <iomanip> // To get access to "std::put_time()" func

#include "../include/tape.hpp"

std::string curtime(const char *format)
{
    std::chrono::system_clock::time_point tp{std::chrono::system_clock::now()};
    time_t tt{std::chrono::system_clock::to_time_t(tp)};
    struct tm *t{localtime(&tt)};
    std::stringstream ss;
    ss << std::put_time(t, format);
    return ss.str();
}

const std::string ITape::kdefault_fname = "tape_default.txt";

void ITape::copyObj(ITape const &obj)
{
    m_filename = obj.m_filename;
    m_tapesize = obj.m_tapesize;
}

void ITape::clearObj(ITape &obj)
{
    obj.m_filename.clear();
    obj.m_tapesize = 0UL;
}

bool ITape::exists(std::string const &fname) const
{
    std::ifstream ifs(fname.c_str());
    return ifs.good();
}

void ITape::create_file(std::string const &fname) const
{
    // Creating file with specified name
    std::ofstream ofs(fname);

    // Check if file was created successfully
    if (ofs.bad())
    {
        std::cerr << "Error: ITape::create_file(std::string const &): can't create file " << fname << '\n';
        return;
    }
    else
#ifdef LOG_INFO
        std::clog << "Log: ITape::create_file(std::string const &): File \"" << fname
                  << "\" created successfully\n";
#endif

    // Closing output file stream
    ofs.close();
}

void ITape::checkexist_create(std::string const &fname) const
{
    if (not ITape::exists(fname))
        ITape::create_file(fname);
}

void ITape::checkexist_create(std::string &&fname) const
{
    if (not ITape::exists(std::move(fname)))
        ITape::create_file(std::move(fname));
}

size_t ITape::get_tapesize() const { return m_tapesize; }

ITape::ITape() : m_filename(kdefault_fname), m_tapesize(kdefault_tapesize) {}

ITape::ITape(std::string const &fname) : m_filename(fname), m_tapesize(kdefault_tapesize) {}

ITape::ITape(std::string &&fname) : m_filename(std::move(fname)), m_tapesize(kdefault_tapesize) {}

ITape::ITape(size_t size) : m_filename(kdefault_fname), m_tapesize(size) {}

ITape::ITape(std::string const &fname, size_t size) : m_filename(fname), m_tapesize(size) {}

ITape::ITape(std::string &&fname, size_t size) : m_filename(std::move(fname)), m_tapesize(size) {}

ITape::ITape(ITape const &obj) { copyObj(obj); }

ITape::ITape(ITape &&lhs) : m_filename(std::move(lhs.m_filename)), m_tapesize(std::move(lhs.m_tapesize)) {}

ITape &ITape::operator=(ITape const &obj)
{
    if (this == &obj)
        return *this;
    copyObj(obj);
    return *this;
}

ITape &ITape::operator=(ITape &&lhs) noexcept
{
    if (this == &lhs)
        return *this;
    clearObj(*this);
    m_filename = std::move(lhs.m_filename);
    m_tapesize = std::move(lhs.m_tapesize);
    return *this;
}

ITape::~ITape() { clearObj(*this); }

std::string const &ITape::get_filename() const { return m_filename; }

void ITape::rename(std::string const &fname) { m_filename = fname; }

void ITape::resize(size_t newsize) { m_tapesize = newsize; }

std::string Tape::copy_content(std::string const &fname) const
{
    // Openning file in "input"/"read" mode
    std::ifstream ifs(fname, std::ios_base::in);

    if (ifs.bad())
    {
        std::cerr << "Error: Tape::copy_content(std::string const &): File \"" << fname
                  << "\" can't be open in read mode\n";
        return "Tape::copy_content(std::string const &) -> error\n";
    }

    std::stringstream ss;

    // Reading buffer from the input file stream to the string stream
    ss << ifs.rdbuf();
    ifs.close();
    return ss.str();
}

size_t Tape::get_tapesize() const { return ITape::get_tapesize(); }

bool Tape::write_to_file_helper(std::vector<int> const &data, std::ios_base::openmode mode,
                                String auto errmsg, [[maybe_unused]] String auto logmsg) const
{
    // Openning file in specified mode
    std::ofstream ofs(get_filename(), mode);

    // Checking if file stream is bad
    if (ofs.bad())
    {
        std::cerr << errmsg;
        return false;
    }

    std::stringstream ss;

    // Writing elements one by one to the file with whitespace separator
    size_t i{};
    for (int const &el : data)
    {
        if (i < max_size())
        {
            ofs << el << ' ';
            ss << el << ", ";
            i++;
        }
        else
            break;
    }

    std::string logdata(ss.str());

    // Erasing unnecessary whitespace with ',' symbol
    if (logdata.find_last_of(", ") != std::string::npos)
        logdata.erase(logdata.find_last_of(", "));
    if (*std::prev(logdata.cend()) == ',')
        logdata.erase(std::prev(logdata.cend()));

#ifdef LOG_INFO
    if (data.size() == 1)
        std::clog << logmsg << ". Written data: (" << *data.cbegin() << ")\n";
    else
        std::clog << logmsg << ". Written data: (" << logdata << ")\n";
#endif

    // Closing file stream
    ofs.close();
    return true;
}

void Tape::write_to_file(String auto funcname, std::vector<int> const &data, std::ios_base::openmode mode) const
{
    // Initializing error and log messages
    std::stringstream errss, logss;
    errss << ERRMSG_WRITE(funcname, data);
    logss << LOGMSG_WRITE(funcname, data);

    // Writing changes to the tape
    write_to_file_helper(data, mode, errss.str(), logss.str());
}

bool Tape::write_to_file_helper(std::vector<int> &&data, std::ios_base::openmode mode,
                                String auto errmsg, [[maybe_unused]] String auto logmsg) const
{
    std::ofstream ofs(get_filename(), mode);
    if (ofs.bad())
    {
        std::cerr << errmsg;
        return false;
    }
    std::stringstream ss;

    size_t i{};
    for (auto &&el : std::move(data))
    {
        if (i < max_size())
        {
            ofs << el << ' ';
            ss << el << ", ";
            i++;
        }
        else
            break;
    }
    std::string logdata(ss.str());
    if (logdata.find_last_of(", ") != std::string::npos)
        logdata.erase(logdata.find_last_of(", "));
    if (*std::prev(logdata.cend()) == ',')
        logdata.erase(std::prev(logdata.cend()));
#ifdef LOG_INFO
    if (data.size() == 1)
        std::clog << logmsg << ". Written data: (" << *std::move(data).cbegin() << ")\n";
    else
        std::clog << logmsg << ". Written data: (" << logdata << ")\n";
#endif
    ofs.close();
    return true;
}

void Tape::write_to_file(String auto funcname, std::vector<int> &&data, std::ios_base::openmode mode) const
{
    std::stringstream errss, logss;
    errss << curtime() << ": " << ERRMSG_WRITE(funcname, std::move(data));
    logss << curtime() << ": " << LOGMSG_WRITE(funcname, std::move(data));
    write_to_file_helper(std::move(data), mode, errss.str(), logss.str());
}

std::vector<int> Tape::read_from_file_helper(String auto errmsg, [[maybe_unused]] String auto logmsg) const
{
    std::ifstream ifs(get_filename());
    if (ifs.bad())
    {
        std::cerr << errmsg;
        return {};
    }

    int num{};
    std::vector<int> v;

    // Copying elements one by one to the vector 'v'
    while (ifs >> num)
        v.push_back(num);

#ifdef LOG_INFO
    std::clog << logmsg;
#endif

    ifs.close();
    return v;
}

std::vector<int> Tape::read_from_file(String auto funcname) const
{
    std::stringstream errss, logss;
    errss << curtime() << ": " << ERRMSG_READ(funcname, get_filename());
    logss << curtime() << ": " << LOGMSG_READ(funcname, get_filename());
    return read_from_file_helper(errss.str(), logss.str());
}

Tape::Tape(std::string const &fname) : ITape(fname) { ITape::checkexist_create(fname); }

Tape::Tape(std::string &&fname) : ITape(fname) { ITape::checkexist_create(fname); }

Tape::Tape(size_t newsize) : ITape(newsize)
{
    if (not ITape::exists(ITape::get_filename()))
        ITape::create_file(ITape::get_filename());
    if (newsize != size())
        resize(newsize);
}

Tape::Tape(std::string const &fname, size_t newsize) : ITape(fname, newsize)
{
    ITape::checkexist_create(fname);
    if (newsize != size())
        resize(newsize);
}

Tape::Tape(std::string &&fname, size_t newsize) : ITape(fname, newsize)
{
    ITape::checkexist_create(fname);
    if (newsize != size())
        resize(newsize);
}

std::string const &Tape::get_filename() const { return ITape::get_filename(); }

void Tape::rename(std::string const &fname)
{
    std::error_code ec;

    // Rename file
    std::filesystem::rename(get_filename(), fname, ec);
    if (ec)
    {
        std::cerr << curtime() << ": Error: Error Code = " << ec << ": Tape::rename(std::string const &): File \""
                  << get_filename() << "\" can't be renamed to \"" << fname << "\"\n";
        return;
    }
#ifdef LOG_INFO
    std::clog << curtime() << ": Log: Tape::rename(std::string const &): File \"" << get_filename()
              << "\" successfully renamed to \"" << fname << "\"\n";
#endif

    // Reassign old filename with new
    ITape::rename(fname);
}

size_t Tape::size() const { return copy_all().size(); }

size_t Tape::max_size() const { return get_tapesize(); }

void Tape::resize(size_t newsize)
{
    ITape::resize(newsize);
    while (size() > newsize)
        pop_back();
}

void Tape::generate_random_tape(size_t count, int from, int to)
{
    // Check if lowest value is bigger than the highest -> swap their values
    if (from > to)
        std::swap(from, to);

    // Preinitializing all elements with zeros to replace them in future
    std::vector<int> vec(count);

    // Create an instance of an engine
    std::random_device rdm_device;

    // Specify engine and distribution
    std::mt19937 engine{rdm_device()};

    // Generating random integer numbers
    std::uniform_int_distribution<int> dist(from, to);
    std::ranges::generate(vec, [&dist, &engine]()
                          { return dist(engine); });
    for (size_t i{}; i < count && i < max_size(); i++)
        push_back(vec.at(i));
}

void Tape::push_front(int data) const
{
    // Check size: 'size()' returns current count of elements in the tape (file)
    // 'max_size()' returns max count of the elements that tape can hold
    if (size() >= max_size())
        return;

    // Copying all content from the tape
    std::vector<int> copy(copy_all());

    // Modifying tape
    copy.insert(copy.cbegin(), data);
    write_to_file(__func__, copy);
}

void Tape::push_front(std::vector<int> const &range) const
{
    if (size() >= max_size() || range.empty())
        return;
    std::vector<int> copy{copy_all()};
    for (size_t i{}; i < range.size() && i <= max_size() - size(); i++)
        copy.insert(copy.cbegin(), range.at(i));
    write_to_file(__func__, copy);
}

void Tape::push_back(int data) const
{
    if (size() >= max_size())
        return;
    write_to_file(__func__, {data}, std::ios_base::app);
}

void Tape::push_back(std::vector<int> const &range) const
{
    if (size() >= max_size())
        return;
    write_to_file(__func__, range, std::ios_base::app);
}

void Tape::emplace_back(std::vector<int> &&range) const
{
    if (size() >= max_size())
        return;
    write_to_file(__func__, std::move(range), std::ios_base::app);
}

void Tape::pop_front() const
{
    std::vector<int> copy{copy_all()};
    if (empty())
        return;
    copy.erase(copy.cbegin());
    write_to_file(__func__, copy);
}

void Tape::pop_back() const
{
    std::vector<int> copy{copy_all()};
    if (empty())
        return;
    copy.erase(std::prev(copy.cend()));
    write_to_file(__func__, copy);
}

void Tape::pop_front(size_t count) const
{
    std::vector<int> copy{copy_all()};
    if (empty())
        return;
    copy.erase(copy.cbegin(), copy.cbegin() + count);
    write_to_file(__func__, copy);
}

void Tape::pop_back(size_t count) const
{
    std::vector<int> copy{copy_all()};
    if (empty())
        return;
    for (size_t i{}; i < count; i++)
        copy.pop_back();
    write_to_file(__func__, copy);
}

int Tape::front() const
{
    std::ifstream ifs(get_filename());
    if (ifs.bad())
    {
        std::cerr << curtime() << ": Error: Tape::front(void): Can't read from file \"" << get_filename() << "\""
                  << ". \'-1\' value will be return\n";
        return -1;
    }
    int num{};

    // Reading one (front) integer from the file
    ifs >> num;
    ifs.close();

#ifdef LOG_INFO
    std::clog << curtime() << ": Log: Tape::front(void): Successfully readed value (" << num
              << ") from the file " << get_filename() << "\"\n";
#endif

    return num;
}

int Tape::back() const { return copy_all().back(); }

std::vector<int> Tape::front_elems(size_t count) const
{
    std::vector<int> fronts, copy{copy_all()};
    for (size_t i{}; i < count && i < copy.size(); i++)
        fronts.push_back(copy.at(i));
    return fronts;
}

std::vector<int> Tape::back_elems(size_t count) const
{
    std::vector<int> backs, copy{copy_all()};
    for (size_t i{}; i < count && i < copy.size(); i++)
        backs.push_back(*(copy.cend() - 1 - i));
    std::ranges::reverse(backs);
    return backs;
}

void Tape::clear() const
{
    // To clear file just open it in "std::ios_base::out" (write/output) mode
    std::ofstream ofs(get_filename());
    if (ofs.bad())
    {
        std::cerr << curtime() << ": Error: Tape::clear(): Can't clear file \"" << get_filename() << "\"\n";
        return;
    }
#ifdef LOG_INFO
    std::clog << curtime() << ": Log: Tape::clear(): Successfully cleared file \"" << get_filename() << "\"\n";
#endif
    ofs.close();
}

bool Tape::empty() const { return std::filesystem::is_empty(get_filename()); }

std::vector<int> Tape::copy_all() const
{
    if (empty())
        return {};
    return read_from_file(__func__);
}
