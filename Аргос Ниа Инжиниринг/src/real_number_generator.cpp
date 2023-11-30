#include <limits>
#include <ranges>
#include <algorithm>

#include "../include/real_number_generator.hpp"

RealNumberGenerator::RealNumberGenerator() : m_engine(m_rdm_dev()) {}

double RealNumberGenerator::generateRandomNumber(double from, double to) noexcept
{
    return std::uniform_real_distribution(from, to + std::numeric_limits<double>::epsilon())(m_engine);
}

std::vector<double> RealNumberGenerator::generateRandomSequence(size_t size, double from, double to)
{
    std::uniform_real_distribution distr(from, to + std::numeric_limits<double>::epsilon());

    std::vector<double> seq(size);
    std::ranges::generate(seq, [&distr, this]()
                          { return distr(this->m_engine); });
    return seq;
}
