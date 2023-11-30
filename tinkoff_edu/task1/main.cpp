#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    // Count of revolvers and amount in dollars that cowboy has
    int n{}, s{};
    std::cin >> n >> s;

    // Price of each revolver
    std::vector<int> prices(n);
    for (int i{}; i < n; i++)
        std::cin >> prices.at(i);

    // Iterator that points on max element in the vector
    auto iter_of_max{std::max_element(std::cbegin(prices), std::cend(prices))};

    // Max price
    int max{*iter_of_max};
    while (max > s)
    {
        // Erasing max value if it greater than amount that has cowboy
        prices.erase(iter_of_max);

        // Updating values of iterator and max value
        iter_of_max = std::max_element(std::cbegin(prices), std::cend(prices));
        max = *iter_of_max;

        // Check if all of the prices are removed - output "0" and exiting from program
        if (prices.empty())
        {
            std::cout << "0\n";
            return EXIT_SUCCESS;
        }
    }

    std::cout << max << '\n';
    return EXIT_SUCCESS;
}
