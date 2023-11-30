#include "../include/tape.hpp"
#include "../include/tapesorter.hpp"

#include <algorithm>
#include <ranges>
#include <filesystem>
#include <iostream>

void TapeSorter::sort(std::string const &srctape, size_t count, std::string const &desttape, size_t restrictbytes) const
{
    // Restriction size of a tape in bytes can't be less than size of integer type
    if (restrictbytes < sizeof(int))
    {
        std::cerr << "Error: TapeSorter::sort(std::string const &, size_t, std::string const &, size_t): "
                  << "Size of tape in bytes can't be less than size of integer type\n";
        return;
    }

    // Initializing input and output tape objects
    Tape in_tape(srctape, count), out_tape(desttape, count);

    // Getting all elements from the input tape to the vector of integers
    std::vector<int> elems(in_tape.copy_all());

    // Creating directory that will contain temporary tapes
    std::filesystem::create_directory("tmp");

    // Iterating by temporary tapes
    for (unsigned i{}; i < separate_tape(count, restrictbytes); i++)
    {
        // Generating name of 'i'-th temporary tape
        std::string tmpname("tmp/" + curtime("%d-%m-%Y_%T"));
        tmpname += std::to_string(i).length() == 1 ? "-00" + std::to_string(i)
                                                   : "-0" + std::to_string(i);

        // Initializing tape object with restricted size
        Tape tmptape(tmpname, tmptape_size(restrictbytes));

        // Filling temporary tape while copy of th input tape is not empty
        size_t j{};
        while (j < tmptape.max_size())
        {
            // Get minimal element from the input tape and add it to temporary tape
            auto iter_of_min{std::ranges::min_element(elems)};
            tmptape.push_back(*iter_of_min);

            // Erasing this min element from the copy of input tape
            elems.erase(iter_of_min);
            j++;
        }
        // Adding to the end of the output tape all elements from the each temporary tape
        out_tape.push_back(tmptape.copy_all());
    }
}

void TapeSorter::sort(std::string &&srctape, size_t count, std::string &&desttape, size_t restrictbytes) const
{
    if (restrictbytes < sizeof(int))
    {
        std::cerr << "Error: TapeSorter::sort(std::string const &, size_t, std::string const &, size_t): "
                  << "Size of tape in bytes can't be less than size of integer type\n";
        return;
    }
    Tape in_tape(std::move(srctape), count), out_tape(std::move(desttape), count);
    std::vector<int> elems(std::move(in_tape.copy_all()));
    std::ranges::sort(std::move(elems));
    std::filesystem::create_directory("tmp");
    for (unsigned i{}; i < separate_tape(count, restrictbytes); i++)
    {
        std::string tmpname("tmp/" + curtime("%d-%m-%Y_%T"));
        tmpname += std::to_string(i).length() == 1 ? "-00" + std::to_string(i)
                                                   : "-0" + std::to_string(i);
        Tape tmptape(std::move(tmpname), tmptape_size(restrictbytes));
        size_t j{};
        while (j < tmptape.max_size())
        {
            auto iter_of_min{std::ranges::min_element(elems)};
            tmptape.emplace_back({*iter_of_min});
            elems.erase(iter_of_min);
            j++;
        }
        out_tape.emplace_back(std::move(tmptape.copy_all()));
    }
}
