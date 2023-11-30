#ifndef REAL_NUMBER_GENERATOR_HPP
#define REAL_NUMBER_GENERATOR_HPP

#include <vector>
#include <random>

/// @brief Generator for real numbers and sequences.
class RealNumberGenerator
{
private:
    double m_from{kdefault_min_value},
        m_to{kdefault_max_value}; // Beginning value and final value to generate: [min, max]
    std::random_device m_rdm_dev; // Random device method
    std::mt19937 m_engine;        // Method of the random nums generation

    static constexpr double kdefault_min_value{0.0}; // Default minimum value
    static constexpr double kdefault_max_value{1.0}; // Default maximum value

public:
    /// @brief Ctor.
    explicit RealNumberGenerator();

    /**
     * @brief Generates a random number within the specified range.
     * @param from The lower bound of the range (inclusive).
     * @param to The upper bound of the range (inclusive).
     * @return A random double value within the specified range.
     */
    double generateRandomNumber(double from = kdefault_min_value,
                                double to = kdefault_max_value) noexcept;

    /**
     * @brief Generates a sequence of random numbers within the default range.
     * @param size The size of the sequence to generate.
     * @param from The lower bound of the range (inclusive).
     * @param to The upper bound of the range (inclusive).
     * @return A vector containing random double values within the default range.
     */
    std::vector<double> generateRandomSequence(size_t size,
                                               double from = kdefault_min_value,
                                               double to = kdefault_max_value);

    /// @brief Dtor.
    virtual ~RealNumberGenerator() {}
};

#endif // !REAL_NUMBER_GENERATOR_HPP
