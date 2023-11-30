#ifndef TAPESORTER_HPP
#define TAPESORTER_HPP

#include <string>

/**
 *  @brief Class that performs sort of the tape to the another tape(-s)
 */
class TapeSorter
{
private:
    /**
     * @brief Calculates size of the temporary tape
     * @param bytes max bytes can tape hold
     * @return Size of the temporary tape
     */
    constexpr size_t tmptape_size(size_t bytes) const { return bytes / sizeof(int); };

    /**
     * @brief Calculates count of the temporaly tapes to separate tapes
     * @param size size of the initial tape
     * @param restrictbytes byte to do restrict by memory
     * @return Count of the tapes
     */
    constexpr unsigned separate_tape(size_t size, size_t restrictbytes) const { return static_cast<unsigned>(size / tmptape_size(restrictbytes)); }

public:
    /// @brief Defaulted ctor
    explicit TapeSorter() = default;

    /// @brief Copy ctor
    explicit TapeSorter(TapeSorter const &) = default;

    /// @brief Move ctor
    explicit TapeSorter(TapeSorter &&) = default;

    /// @brief Copy-assignment operator
    TapeSorter &operator=(TapeSorter const &) = default;

    /// @brief Move-assignment operator
    TapeSorter &operator=(TapeSorter &&) noexcept = default;

    /// @brief Defaulted dtor
    virtual ~TapeSorter() = default;

    /**
     * @brief Sorting all elements from input tape and write them (sorted) into the output tape
     * (Creates temporary tapes in dir 'tmp')
     * @param srctape name of the source (input) tape
     * @param count count of elements in input tape
     * @param desttape name of the destination (output) tape
     * @param restrictbytes byte restriction
     */
    void sort(std::string const &srctape, size_t count, std::string const &desttape, size_t restrictbytes) const;

    /**
     * @brief Sorting all elements from input tape and write them (sorted) into the output tape (move version)
     * (Creates temporary tapes in dir 'tmp')
     * @param srctape name of the source (input) tape
     * @param count count of elements in input tape
     * @param desttape name of the destination (output) tape
     * @param restrictbytes byte restriction
     */
    void sort(std::string &&srctape, size_t count, std::string &&desttape, size_t restrictbytes) const;
};

#endif // !TAPESORTER_HPP
