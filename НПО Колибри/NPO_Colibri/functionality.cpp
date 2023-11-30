#include <algorithm>
#include <fstream>
#include <iterator>
#include <regex>

#include "functionality.hpp"
#include "menu.hpp"
#include "settings.hpp"

std::string readFileToStr(const char *file)
{
    std::ifstream ifs(file);
    std::stringstream ss;

    // Reading all content from the file to string stream
    ss << ifs.rdbuf();

    // Closing stream
    ifs.close();

    return ss.str();
}

void modifyFile(char const *in, char const *out, uint64_t xor_value)
{
    // Copying content to the string instance
    std::string content{readFileToStr(in)};

    // Changing each byte with XOR op
    for (auto &ch : content)
        ch ^= xor_value;

    std::ofstream ofs(out, std::ios_base::binary);
    if (!ofs.is_open()) {
        ERRMSG("Can't open file in a binary mode. Skipping modification\n");
        return;
    }

    // Writing changes to the output file
    ofs << content;
    ofs.close();

    std::cout << "File " << in << " was successfully modified and put all content to the file "
              << out << "\n";
}

std::vector<std::string> getFilenamesByMask(std::filesystem::path const &path,
                                            std::string const &mask)
{
    std::vector<std::string> files;
    std::regex pattern(mask);

    for (auto const &file : std::filesystem::directory_iterator(path))
        if (std::filesystem::is_regular_file(file)) {
            std::string filename{file.path().filename().string()};

            // If 'filename' matches with the pattern - add it to vector of files
            if (std::regex_match(filename, pattern))
                files.emplace_back(filename);
        }

    return files;
}

void modifyFileHandler(std::vector<std::string> const &files, Configurations config)
{
    // Storing all output files
    std::vector<std::string> outFiles;

    for (size_t i{}; i < files.size(); i++) {
        std::string out;
        std::cout << "Type name of the output file " << i + 1 << ": ";
        std::getline(std::cin, out);

        // Adding name of the each output file
        outFiles.push_back(out);

        // Check if output filename is already in the vector
        if (std::find(std::cbegin(outFiles), std::cend(outFiles), out) != std::cend(outFiles)) {
            // Checking action: what to do if file repeats
            switch (config.action) {
            case Actions_To_Repeating_Files::OVERWRITE: {
                // Creating absolute path to the each output file
                out.insert(0ul, config.outPath.c_str());

                // Modifying each file one by one
                modifyFile(files.at(i).c_str(), out.c_str(), config.xor_value);
                break;
            }
            case Actions_To_Repeating_Files::MODIFICATION: {
                // We would add info from another input file to the repeating output
                std::string content{readFileToStr(files.at(i).c_str())};
                for (auto &ch : content)
                    ch ^= config.xor_value;
                std::ofstream ofs(out, std::ios_base::app);
                if (!ofs.is_open()) {
                    ERRMSG("Can't open file in a binary mode. Skipping modification\n");
                    return;
                }
                ofs << "\n\nInfo from " << files.at(i) << " to " << out << ":\n" << content;
                ofs.close();
                break;
            }
            case Actions_To_Repeating_Files::COUNTER_TO_FILE: {
                out.insert(0ul, config.outPath.c_str());

                // Adding counter to the output files
                out.insert(out.length() - 1, std::to_string(i).c_str());

                modifyFile(files.at(i).c_str(), out.c_str(), config.xor_value);
                break;
            }
            default:
                ERRMSG("Something gets wrong. Skipping modification\n");
                break;
            }
        }
        // If there is no repeating output files, just modify them
        else {
            out.insert(0ul, config.outPath.c_str());
            modifyFile(files.at(i).c_str(), out.c_str(), config.xor_value);
        }
    }

    // Necessity of the removing input files
    if (config.deleteInputFiles == true)
        // Removing all input files
        for (auto const &inFile : files)
            std::filesystem::remove(inFile);
}
