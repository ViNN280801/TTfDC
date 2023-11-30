#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string_view>
#include <string>

#include "include/surface.hpp"
#include "include/particle.hpp"
#include "include/real_number_generator.hpp"

void clearLogFile(std::string_view filename)
{
    std::ofstream ofs(std::string(filename), std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

int main()
{
    // Test for Surface class
    SimpleSurface surface(1.0, 2.0, -3.0, 4.0);
    coordinates_t pointOnSurface{1.0, -1.0, 2.0};
    coordinates_t pointNotOnSurface{2.0, 1.0, 5.0};

    assert(surface.intersectsSurface(pointOnSurface) == false);
    assert(surface.intersectsSurface(pointNotOnSurface) == false);

    // Test for Particle class
    {
        // Test default constructor
        Particle particle1;
        particle1.printData(); // Output particle data to console

        // Test copy constructor and operator=
        Particle particle2{Particle(particle1)}, particle3;
        particle3 = particle1;

        assert(particle1 != particle2);
        assert(particle2 != particle3);

        // Test intersectsSurface method
        SimpleSurface surface(0.0, 0.0, 0.0, 100.0); // Example surface
        assert(not particle1.intersectsSurface(surface));

        // Test handleIntersection method
        const std::string logFileName{"log.txt"};
        clearLogFile(logFileName); // Clear log file before test

        particle1.handleIntersection(surface, logFileName); // Not intersects
        std::ifstream ifs(logFileName);
        assert(ifs.good()); // Check if log file is created

        SimpleSurface surface2(1.0, -1.0, 1.0, 0.0);
        Particle pIntersects{Particle::createRandomParticleOnSimpleSurface(surface2)};
        assert(pIntersects.intersectsSurface(surface2));
        pIntersects.handleIntersection(surface2, logFileName);

        ifs.close();
    }

    // Test for RealNumberGenerator class
    {
        RealNumberGenerator rng;

        // Test generateRandomNumber method
        double randomNumber = rng.generateRandomNumber(0.0, 10.0);
        assert(randomNumber >= 0.0 && randomNumber <= 10.0);

        // Test generateRandomSequence method
        size_t seqSize = 100ul;
        std::vector<double> seq = rng.generateRandomSequence(seqSize, -100.0, 100.0);
        for (double num : seq)
            assert(num >= -100.0 && num <= 100.0);
    }

    std::cout << "\033[1;32mAll tests passed successfully!\033[0m\n";

    return EXIT_SUCCESS;
}
