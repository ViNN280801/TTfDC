#ifndef TAPE_HPP
#define TAPE_HPP

#define VARNAME(var) #var
#define TYPEOFVAR(var) typeid(var).name()

#define ERRMSG_WRITE(funcname, var) "Error: Tape::" << funcname << '(' << TYPEOFVAR(var) << ' ' << VARNAME(var) << "): " \
                                                    << "Can't add item(-s) to the tape\n"
#define LOGMSG_WRITE(funcname, var) "Log: Tape::" << funcname << '(' << TYPEOFVAR(var) << ' ' << VARNAME(var) << "): " \
                                                  << "Successfully added item(-s) to the beginning of the tape"
#define ERRMSG_READ(funcname, fname) "Error: Tape::" << funcname << "(): Can't open file \"" << fname << "\" in read mode. " \
                                                     << "Returning empty range\n"
#define LOGMSG_READ(funcname, fname) "Log: Tape::" << funcname << "(): Successfully copied all elements from the file \"" \
                                                   << fname << "\" to the vector\n"

#include <string>
#include <vector>
#include <fstream>
#include <concepts> // To make 'String' concept

/* Concept that specifies all types that can be convert to "std::string_view" type
For example, "char", "const char *", "std::string", etc. */
template <typename T>
concept String = std::is_convertible_v<T, std::string_view>;

/**
 * @brief Gets current time in specified format
 * @param format format to display time
 * @return Time as "std::string"
 */
std::string curtime(const char *format = "%d/%m/%Y %T");

/**
 * @brief Abstract class of data storage device representing a magnetic tape.
 * This data type have bidirectional access (random access is unallowed)
 */
class ITape
{
private:
    std::string m_filename; // Name of the file that represents data storage
    size_t m_tapesize;      // Size of a tape

    /**
     * @brief Copies data from the specified object to current
     * @param obj object to copy data from it
     */
    void copyObj(ITape const &obj);

    /**
     * @brief Clears out all content from specified object
     * @param obj object to clear out it's content
     */
    void clearObj(ITape &obj);

    static const std::string kdefault_fname;          // Default name of the file
    static constexpr size_t kdefault_tapesize{100UL}; // Default size of a tape

protected:
    /**
     * @brief Checker of existence of specified file
     * @param fname name of the file to do existence check
     * @return "true" if file exists, "false" otherwise
     */
    bool exists(std::string const &fname) const;

    /**
     * @brief Creates file with specified name
     * @param fname name of file to create
     */
    void create_file(std::string const &fname) const;

    /**
     * @brief Helper func to do existence of file check and
     * creating file if file don't exist
     * @param fname name of the file to create and perform check
     */
    void checkexist_create(std::string const &fname) const;

    /**
     * @brief Helper func to do existence of file check and
     * creating file if file don't exist (move version)
     * @param fname name of the file to create and perform check
     */
    void checkexist_create(std::string &&fname) const;

    /**
     * @brief Getter for size of a tape
     * @return Size of a current tape object
     */
    size_t get_tapesize() const;

public:
    /// @brief Ctor
    explicit ITape();

    /**
     * @brief Ctor with filename param
     * @param fname name of the file
     */
    explicit ITape(std::string const &fname);

    /**
     * @brief Ctor with filename param with move semantics
     * @param fname name of the file
     */
    explicit ITape(std::string &&fname);

    /**
     * @brief Ctor with specified size of a tape
     * @param size count of elements which tape can hold (max size)
     */
    explicit ITape(size_t size);

    /**
     * @brief Ctor with specified filename and size of a tape
     * @param fname name of the file
     * @param size count of elements which tape can hold (max size)
     */
    explicit ITape(std::string const &fname, size_t size);

    /**
     * @brief Ctor with specified filename with move semantics and size of a tape
     * @param fname name of the file
     * @param size count of elements which tape can hold (max size)
     */
    explicit ITape(std::string &&fname, size_t size);

    /**
     * @brief Copy ctor
     * @param obj object to copy to current object
     */
    explicit ITape(ITape const &obj);

    /**
     * @brief Move ctor
     * @param lhs object to move
     */
    explicit ITape(ITape &&lhs);

    /**
     * @brief Copy-assignment operator
     * @param obj object to copy it content to current object
     */
    ITape &operator=(ITape const &obj);

    /**
     * @brief Move-assignament operator
     * @param lhs object to move
     */
    ITape &operator=(ITape &&lhs) noexcept;

    /// @brief Dtor
    virtual ~ITape();

    /**
     * @brief Getter for filename
     * @return Ref to const filename of current object
     */
    std::string const &get_filename() const;

    /**
     * @brief Setter for filename
     * Modifies filename of current object to specified
     * @param fname new file name
     */
    void rename(std::string const &fname);

    /**
     * @brief Setter for size of a tape
     * @param newsize new size of a tape
     */
    void resize(size_t newsize);

    /* --- Pure virtual funcs --- */
    virtual void push_front(int) const = 0;
    virtual void push_front(std::vector<int> const &) const = 0;
    virtual void push_back(int) const = 0;
    virtual void push_back(std::vector<int> const &) const = 0;
    virtual void emplace_back(std::vector<int> &&) const = 0;
    virtual void pop_front() const = 0;
    virtual void pop_back() const = 0;
    virtual void pop_front(size_t) const = 0;
    virtual void pop_back(size_t) const = 0;
    virtual int front() const = 0;
    virtual int back() const = 0;
    virtual std::vector<int> front_elems(size_t) const = 0;
    virtual std::vector<int> back_elems(size_t) const = 0;
    virtual std::vector<int> copy_all() const = 0;
    /* --- End of pure virtual funcs --- */
};

/**
 * @brief This class represents implementation of the interface 'ITape'
 */
class Tape : ITape
{
private:
    /**
     * @brief Copies all content from file to the string
     * @param fname name of the file
     * @return All content from the specified file as a "std::string"
     */
    std::string copy_content(std::string const &fname) const;

    /**
     * @brief Getter for size of a tape
     * @return Size of a current tape object
     */
    size_t get_tapesize() const;

    /**
     * @brief Writes specified list of integers to the file with specified open mode
     * @param data list of integers to write them into the tape
     * @param mode mode to open tape (file): "std::ios_base::out", "std::ios_base::app", etc.
     * @tparam errmsg error message
     * @tparam logmsg log message
     * @return "true" if data had been successfully writes, "false" otherwise
     */
    bool write_to_file_helper(std::vector<int> const &data, std::ios_base::openmode mode,
                              String auto errmsg, String auto logmsg) const;

    /**
     * @brief Automatically generates error and log messages and writes specified data to the tape
     * @tparam funcname name of the function (use "__func__" to get it)
     * @param data data to write to the tape
     * @param mode mode to open tape (file): "std::ios_base::out", "std::ios_base::app", etc.
     */
    void write_to_file(String auto, std::vector<int> const &data,
                       std::ios_base::openmode mode = std::ios_base::out) const;

    /**
     * @brief Writes specified list of integers to the file with specified open mode (move version)
     * @param data list of integers to write them into the tape
     * @param mode mode to open tape (file): "std::ios_base::out", "std::ios_base::app", etc.
     * @tparam errmsg error message
     * @tparam logmsg log message
     * @return "true" if data had been successfully writes, "false" otherwise
     */
    bool write_to_file_helper(std::vector<int> &&data, std::ios_base::openmode mode,
                              String auto errmsg, String auto logmsg) const;

    /**
     * @brief Automatically generates error and log messages and writes specified data to the tape (move version)
     * @tparam funcname name of the function (use "__func__" to get it)
     * @param data data to write to the tape
     * @param mode mode to open tape (file): "std::ios_base::out", "std::ios_base::app", etc.
     */
    void write_to_file(String auto funcname, std::vector<int> &&data,
                       std::ios_base::openmode mode = std::ios_base::out) const;

    /**
     * @brief Copies all content from the file to the "std::vector" of integers
     * @tparam errmsg error message
     * @tparam logmsg log message
     * @return All content of the file represented as "std::vector<int>"
     */
    std::vector<int> read_from_file_helper(String auto errmsg, String auto logmsg) const;

    /**
     * @brief Copies all content from the file to the "std::vector" of integers
     * @tparam funcname name of the function (use "__func__" to get it)
     * @return All content of the file represented as "std::vector<int>"
     */
    std::vector<int> read_from_file(String auto funcname) const;

public:
    /// @brief Defaulted ctor
    explicit Tape() = default;

    /**
     * @brief Ctor with filename param
     * @param fname name of the file
     */
    explicit Tape(std::string const &fname);

    /**
     * @brief Move ctor with filename param
     * @param fname name of the file
     */
    explicit Tape(std::string &&fname);

    /**
     * @brief Ctor with specified size of a tape
     * @param size count of elements which tape can hold (max size)
     */
    explicit Tape(size_t size);

    /**
     * @brief Ctor with specified filename and size of a tape
     * @param fname name of the file
     * @param size count of elements which tape can hold (max size)
     */
    explicit Tape(std::string const &fname, size_t size);

    /**
     * @brief Ctor with specified filename with move semantics and size of a tape
     * @param fname name of the file
     * @param size count of elements which tape can hold (max size)
     */
    explicit Tape(std::string &&fname, size_t size);

    /// @brief Defaulted copy ctor
    explicit Tape(Tape const &) = default;

    /// @brief Defaulted move ctor
    explicit Tape(Tape &&) = default;

    /// @brief Defaulted copy-assignment operator
    Tape &operator=(Tape const &) = default;

    /// @brief Defaulted move-assignment operator
    Tape &operator=(Tape &&) noexcept = default;

    /// @brief Defaulted virtual dtor
    virtual ~Tape() = default;

    /**
     * @brief Getter for filename
     * @return Ref to const filename of current object
     */
    std::string const &get_filename() const;

    /**
     * @brief Setter for filename.
     * Modifies filename of current object to specified
     * @param fname new file name
     */
    void rename(std::string const &fname);

    /// @return Current size of the tape
    size_t size() const;

    /// @return Max size of the tape is able to hold
    size_t max_size() const;

    /**
     * @brief Setter for size of a tape
     * @param newsize new size of a tape
     */
    void resize(size_t newsize);

    /**
     * @brief Generates random tape of integers in specified interval
     * @param count count of elements to generate
     * @param from lowest integer
     * @param to highest integer
     */
    void generate_random_tape(size_t count, int from = 0, int to = 1000);

    /**
     * @brief Adds one integer element to the beginning of the file
     * {See methods: 'get_filename()', 'rename'}
     * @param data element to add
     */
    void push_front(int data) const;

    /**
     * @brief Adds integer range to the beginning of the file
     * {See methods: 'get_filename()', 'rename'}
     * @param range some elements to add
     */
    void push_front(std::vector<int> const &range) const;

    /**
     * @brief Adds one integer element to the end of the file
     * {See methods: 'get_filename()', 'rename'}
     * @param data element to add
     */
    void push_back(int data) const;

    /**
     * @brief Adds integer range to the end of the file
     * {See methods: 'get_filename()', 'rename'}
     * @param range some elements to add
     */
    void push_back(std::vector<int> const &range) const;

    /**
     * @brief Adds integer range to the end of the file (move version)
     * {See methods: 'get_filename()', 'rename'}
     * @param range some elements to add
     */
    void emplace_back(std::vector<int> &&range) const;

    /// @brief Removes element from the beginning of the file
    void pop_front() const;

    /// @brief Removes element from the end of the file
    void pop_back() const;

    /**
     * @brief Removes specified count of elements from the beginning of the file (tape)
     * @param count count of elements to remove
     */
    void pop_front(size_t count) const;

    /**
     * @brief Removes specified count of elements from the end of the file (tape)
     * @param count count of elements to remove
     */
    void pop_back(size_t count) const;

    /**
     * @brief Get access to front element of the file (tape)
     * @return Front element
     */
    int front() const;

    /**
     * @brief Get access to back element of the file (tape)
     * @return Back element
     */
    int back() const;

    /**
     * @brief Get access to specified count of front elements from the file (tape)
     * @param count count of elements
     * @return Specified count of front elements
     */
    std::vector<int> front_elems(size_t count) const;

    /**
     * @brief Get access to specified count of back elements from the file (tape)
     * @param count count of elements
     * @return Specified count of back elements
     */
    std::vector<int> back_elems(size_t count) const;

    /// @brief Removes all elements from the file (tape)
    void clear() const;

    /**
     * @brief Check if file (tape) is empty
     * @return "true" if tape is empty, "false" otherwise
     */
    bool empty() const;

    /**
     * @brief Copies all integer elements from the file (tape) to the "std::vector"
     * @return Range of elements from the file
     */
    std::vector<int> copy_all() const;
};

#endif // !TAPE_HPP
