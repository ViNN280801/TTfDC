#include <iostream>
#include <span>
#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include <concepts>

/**
 * @brief Concept that checks available of all comparison operators
 * @tparam a first variable
 * @tparam b second variable
 */
template <typename T>
concept Comparable = requires(T a, T b) {
    {
        a < b
    } -> std::convertible_to<bool>;
    {
        a == b
    } -> std::convertible_to<bool>;
    {
        a != b
    } -> std::convertible_to<bool>;
    {
        a > b
    } -> std::convertible_to<bool>;
    {
        a <= b
    } -> std::convertible_to<bool>;
    {
        a >= b
    } -> std::convertible_to<bool>;
};

/**
 * @brief Concept that checks if variable has output operator
 * @tparam a variable to check
 * @param os output stream
 */
template <typename T>
concept HasOutputOperator = requires(T a, std::ostream &os) {
    {
        os << a
    } -> std::same_as<std::ostream &>;
};

/**
 * @brief Fills vector with integer values
 * @param v vector
 * @param from min value to generate
 * @param to max value to generate
 */
void fillVector(std::vector<int> &v, int from = 0, int to = 100)
{
    std::random_device seeder;

    // If "std::random_device" doesn't have an entropy -> using old C-style seed
    // represented as a current time in "unsigned long" representation
    // Otherwise call the ctor of the "std::random_device" instance
    const auto seed{seeder.entropy() ? seeder() : time(nullptr)};

    // Using Mersene twister engine as generator of integer numbers
    std::mt19937 engine{static_cast<std::mt19937::result_type>(seed)};
    std::uniform_int_distribution<int> uid{from, to};
    auto generator{std::bind(uid, engine)};
    std::generate(std::begin(v), std::end(v), generator);
}

/**
 * @brief Prints all elements of the sequence to terminal
 * @tparam range range to print it elements
 */
template <HasOutputOperator T>
void printRange(std::span<T const> range)
{
    for (auto const &el : range)
        std::cout << el << ' ';
    std::endl(std::cout);
}

/**
 * @brief Recursive func helper for merge sort
 * @tparam arr array of elements -> arr[start;end)
 * @tparam result result vector
 * @param start left index
 * @param end right index
 */
template <Comparable T>
constexpr void mergeSortHelper(std::vector<T> &arr, std::vector<T> &result, size_t start, size_t end)
{
    // Base case: if array consist of 1 element - do nothing
    if (end - start <= 1ul)
        return;
    // If array consist of 2 elements and it's need to swap them - swap them
    if (end - start == 2ul)
    {
        if (result.at(start) > result.at(start + 1))
            std::swap(result.at(start), result.at(start + 1));
        return;
    }

    size_t middle{(start + end) / 2};

    mergeSortHelper(result, arr, start, middle);
    mergeSortHelper(result, arr, middle, end);

    // Merging left and right subarrays
    // 'k' - index for result array
    size_t i{start}, j{middle}, k{start};

    // Filling result subarray with sorted values
    while (k < end)
    {
        if (j >= end || (i < middle && arr.at(i) < arr.at(j)))
        {
            // Filling with elements of left subarray
            result.at(k) = arr.at(i);
            i++;
        }
        else
        {
            // Filling with elements with right subarray
            result.at(k) = arr.at(j);
            j++;
        }
        k++;
    }
}

/**
 * @brief Merge sort function. Best, middle and worth cases: 0(n*log(n))
 * @tparam vec array of elements
 */
template <Comparable T>
constexpr void mergeSort(std::vector<T> &vec)
{
    std::vector<T> copy(vec);
    mergeSortHelper(copy, vec, 0, vec.size());
}

int main()
{
    std::vector<int> v(10);
    fillVector(v);
    printRange<int>(v);
    mergeSort(v);
    printRange<int>(v);

    return EXIT_SUCCESS;
}
