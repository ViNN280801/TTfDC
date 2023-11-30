#include <iostream>
#include <span>

#include "../include/tape.hpp"

template <typename T>
void print_range(std::span<T const> range)
{
    for (auto const &el : range)
        std::cout << el << ' ';
    std::endl(std::cout);
}

int main()
{
    Tape t("newfname", 10);
    t.push_front(5);
    for (int i{}; i < 10; i++)
        t.push_back(i);
    std::vector v{54, 34, 879, 123, 92, 238490};
    t.push_front(v);
    t.push_front(v);
    t.push_back(1000);
    t.push_back(158);
    t.push_front(155);
    t.push_front(156);
    t.push_back(157);
    for (int i{}; i < 10; i++)
        t.push_back(i * 2);
    t.pop_back();
    t.pop_front();
    t.pop_back(5);
    t.pop_front(3);
    t.push_back(v);
    t.push_back(v);

    for (int i{}; i < 10; i++)
        t.push_front(i);

    for (auto const &el : t.front_elems(5))
        std::cout << el << ' ';
    std::endl(std::cout);

    for (auto const &el : t.back_elems(3))
        std::cout << el << ' ';
    std::endl(std::cout);

    std::cout << t.empty() << std::endl;
    t.resize(15);
    t.generate_random_tape(15);
    std::cout << "Current size = " << t.size() << "\tMax size = " << t.max_size() << std::endl;

    return EXIT_SUCCESS;
}
