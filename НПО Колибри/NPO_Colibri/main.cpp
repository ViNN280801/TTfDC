#include <chrono>
#include <iostream>
#include <thread>

#include "functionality.hpp"
#include "menu.hpp"

int main()
{
    // Getting all configurations
    Configurations config{handleMenu()};

    // Getting all input filenames by mask
    std::vector<std::string> filenames{getFilenamesByMask()};
    std::cout << "The following files were found: ";

    // Printing found files
    for (size_t i{}; i < filenames.size(); i++)
        if (i != filenames.size() - 1)
            std::cout << filenames.at(i) << "; ";
        else
            std::cout << filenames.at(i);
    std::endl(std::cout);

    if (config.startConfig == true) {
        std::cout << "Timer mode selected. Polling every " << config.pollingFrequency << " ms\n";

        // Use a loop to periodically check and modify files
        while (true) {
            modifyFileHandler(filenames, config);
            std::this_thread::sleep_for(std::chrono::milliseconds(config.pollingFrequency));
        }
    } else {
        std::cout << "Once start mode selected\n";
        modifyFileHandler(filenames, config);
    }

    return EXIT_SUCCESS;
}
