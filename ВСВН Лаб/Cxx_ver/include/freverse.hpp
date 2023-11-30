#ifndef FREVERSE_HPP
#define FREVERSE_HPP

/* Macro to get variable name and it's type */
#define VARNAME(var) #var
#define TYPEOFVAR(var) typeid(var).name()

/* Macro to generate error and log msgs with */
#define ERRMSG(desc) curtime() << ": Error: " << __PRETTY_FUNCTION__ << ": " << desc
#define LOGMSG(desc) curtime() << ": Log: " << __PRETTY_FUNCTION__ << ": " << desc

#include <string>

/**
 * @brief Gets current time in specified format
 * @param format format to display time
 * @return Time as "std::string"
 */
std::string curtime(const char *format = "%d/%m/%Y %T");

/**
 * @brief Purpose of this class is reverse bytes in specified file
 */
class freverse
{
private:
    std::string m_fname;
    static constexpr std::string kdefault_fname{"text.txt"};

protected:
    /**
     * @brief Checker of existence of specified file
     * @param fname name of the file to do existence check
     * @return "true" if file exists, "false" otherwise
     */
    bool exists(std::string const &fname) const;

    /**
     * @brief Creates file in current directory
     * @param fname name of the file to create
     */
    void create_file(std::string const &fname) const;

    /**
     * @brief Helper func to do existence of file check and
     * creating file if file don't exist
     * @param fname name of the file to create and perform check
     */
    void check_existance_create(std::string const &fname) const;

    /**
     * @brief Renames file with name 'm_fname'
     * @param newfname new file name to rename name of the current object
     */
    void change_fname(std::string const &newfname);

public:
    /// @brief Default ctor
    explicit freverse();

    /**
     * @brief Ctor with param
     * @param newfname new file name to replace it
     */
    explicit freverse(std::string const &newfname);

    /**
     * @brief Ctor with param (move ver)
     * @param newfname new file name to replace it
     */
    explicit freverse(std::string &&newfname);

    /// @brief Copy ctor
    explicit freverse(freverse const &rhs);

    /// @brief Move ctor
    explicit freverse(freverse &&lhs) noexcept;

    /// @brief Copy assignment operator
    freverse &operator=(freverse const &rhs);

    /// @brief Move assignment operator
    freverse &operator=(freverse &&lhs) noexcept;

    /// @brief Dtor
    virtual ~freverse();

    /**
     * @brief Getter for name of the file
     * @return Name of the file
     */
    const std::string get_filename() const;

    /**
     * @brief Setter for name of the file
     * @param newfname new file name
     */
    void rename(std::string const &newfname);

    /**
     * @brief Setter for name of the file (move ver)
     * @param lhs new file name
     */
    void rename(std::string &&newfname);

    /**
     * @brief Gets all bytes from input file, reverse it and put into output file
     * @param inf name of the input file
     * @param outf name of the output file
     */
    void reverse(std::string const &inf, std::string const &outf) const;
};

#endif // !FREVERSE_HPP
