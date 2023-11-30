#include <iostream>
#include <string>
#include <iterator>

static const std::string sheriff{"sheriff"};

int main()
{
    std::string s;
    std::getline(std::cin, s, '\n');

    // Counter for word "sheriff"
    int counter{};

    // Iterating by string "sheriff" to find and erase certain letters one by one
    for (size_t i{}; i < sheriff.length(); i++)
    {
        size_t letter_pos{s.find(sheriff.at(i))};
        
        // Checking "find()" method returned result
        if (letter_pos != std::string::npos)
        {
            // Erasing from user's string certain found letter
            s.erase(letter_pos, 1);
        }
        else
            break;

        // If 'i' is the position of last letter
        // It means that we complete word "sheriff"
        if (i == sheriff.length() - 1)
        {
            // Incrementing counter of words "sheriff"
            counter++;

            // Move backwards to the first letter
            i = 0;
        }
    }

    std::cout << counter << '\n';

    return EXIT_SUCCESS;
}
