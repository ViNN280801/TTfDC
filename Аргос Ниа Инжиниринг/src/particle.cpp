#include <limits>
#include <iostream>
#include <format>
#include <cmath>
#include <fstream>
#include <string>

#include "../include/particle.hpp"
#include "../include/real_number_generator.hpp"

struct Particle::ParticleImpl
{
    /* === Constants === */
    static constexpr double kdefault_weight{1.0e-10};
    static constexpr double kdefault_velocity{10};
    static constexpr long double kdefault_charge{std::numeric_limits<long double>::epsilon()};

    /// @brief Coordinates of the particle in Cartesian form.
    coordinates_t m_coordinates;

    /// @brief Physics parameters of the particle (weight, velocity and charge).
    struct physic_params_t
    {
        double weight{kdefault_weight};      // Weight of the particle (kg).
        double velocity{kdefault_velocity};  // Velocity of the particle (m/s).
        long double charge{kdefault_charge}; // Electrical charge of the particle (C - coulomb]).

        /// @brief Ctor.
        physic_params_t() {}
    } m_physic_params;
};

void Particle::prvt_copy(Particle const &other)
{
    if (other.m_ptcl)
        m_ptcl = std::make_unique<ParticleImpl>(*other.m_ptcl);
    else
    {
        m_ptcl.reset();
        return;
    }

    m_ptcl->m_coordinates.x += std::numeric_limits<double>::epsilon();
    m_ptcl->m_coordinates.y += std::numeric_limits<double>::epsilon();
    m_ptcl->m_coordinates.z += std::numeric_limits<double>::epsilon();
}

void Particle::prvt_record_intersection(coordinates_t const &coordinates, std::string_view filename) const
{
    std::ofstream ofs(std::string(filename), std::ios::app);
    if (ofs.is_open())
    {
        ofs << std::format("{} {} {}\n", coordinates.x, coordinates.y, coordinates.z);
        ofs.close();
    }
    else
        std::cerr << std::format("Can't open log file \'{}\' for writing.\n", filename);
}

void Particle::prvt_destroy() { m_ptcl.reset(); }

Particle::Particle() : m_ptcl(std::make_unique<ParticleImpl>()) {}

Particle::Particle(Particle const &other) { prvt_copy(other); }

Particle &Particle::operator=(Particle const &other)
{
    // Check self-assignment
    if (this == std::addressof(other))
        return *this;
    prvt_copy(other);
    return *this;
}

bool operator<(Particle const &lhs, Particle const &rhs)
{
    coordinates_t lhsCoords{lhs.getParticleCoordinates()},
        rhsCoords{rhs.getParticleCoordinates()};

    // Compare coordinates
    if (lhsCoords.x != rhsCoords.x)
        return lhsCoords.x < rhsCoords.x;
    else if (lhsCoords.y != rhsCoords.y)
        return lhsCoords.y < rhsCoords.y;
    else if (lhsCoords.z != rhsCoords.z)
        return lhsCoords.z < rhsCoords.z;

    // Compare other physical parameters
    if (lhs.m_ptcl->m_physic_params.weight != rhs.m_ptcl->m_physic_params.weight)
        return lhs.m_ptcl->m_physic_params.weight < rhs.m_ptcl->m_physic_params.weight;
    else if (lhs.m_ptcl->m_physic_params.velocity != rhs.m_ptcl->m_physic_params.velocity)
        return lhs.m_ptcl->m_physic_params.velocity < rhs.m_ptcl->m_physic_params.velocity;
    else if (lhs.m_ptcl->m_physic_params.charge != rhs.m_ptcl->m_physic_params.charge)
        return lhs.m_ptcl->m_physic_params.charge < rhs.m_ptcl->m_physic_params.charge;

    // If all characteristics are equal, returning `false`
    return false;
}

bool operator>(Particle const &lhs, Particle const &rhs) { return not(lhs < rhs); }

bool operator<=(Particle const &lhs, Particle const &rhs)
{
    coordinates_t lhsCoords{lhs.getParticleCoordinates()},
        rhsCoords{rhs.getParticleCoordinates()};

    // Compare coordinates
    if (lhsCoords.x != rhsCoords.x)
        return lhsCoords.x <= rhsCoords.x;
    else if (lhsCoords.y != rhsCoords.y)
        return lhsCoords.y <= rhsCoords.y;
    else if (lhsCoords.z != rhsCoords.z)
        return lhsCoords.z <= rhsCoords.z;

    // Compare other physical parameters
    if (lhs.m_ptcl->m_physic_params.weight != rhs.m_ptcl->m_physic_params.weight)
        return lhs.m_ptcl->m_physic_params.weight <= rhs.m_ptcl->m_physic_params.weight;
    else if (lhs.m_ptcl->m_physic_params.velocity != rhs.m_ptcl->m_physic_params.velocity)
        return lhs.m_ptcl->m_physic_params.velocity <= rhs.m_ptcl->m_physic_params.velocity;
    else if (lhs.m_ptcl->m_physic_params.charge != rhs.m_ptcl->m_physic_params.charge)
        return lhs.m_ptcl->m_physic_params.charge <= rhs.m_ptcl->m_physic_params.charge;

    // If all characteristics are equal, returning `false`
    return false;
}

bool operator>=(Particle const &lhs, Particle const &rhs) { return not(lhs <= rhs); }

bool operator==(Particle const &lhs, Particle const &rhs)
{
    // If both of ptrs points to the same memory - particles are equals
    return (lhs.m_ptcl == rhs.m_ptcl);
}

bool operator!=(Particle const &lhs, Particle const &rhs) { return not(lhs == rhs); }

std::ostream &operator<<(std::ostream &os, Particle const &particle)
{
    os << std::format("x: {}\ny: {}\nz: {}\nWeight: {} [kg]\nVelocity: {} [m/s]\nCharge: {} [C]\n\n",
                      particle.m_ptcl->m_coordinates.x,
                      particle.m_ptcl->m_coordinates.y,
                      particle.m_ptcl->m_coordinates.z,
                      particle.m_ptcl->m_physic_params.weight,
                      particle.m_ptcl->m_physic_params.velocity,
                      particle.m_ptcl->m_physic_params.charge);
    return os;
}

Particle::~Particle() { prvt_destroy(); }

void Particle::printData() const noexcept { std::cout << *this; }

Particle::ParticleImpl &Particle::data() noexcept(false)
{
    if (!m_ptcl)
    {
        prvt_destroy();
        throw std::runtime_error("No underlying object available here");
    }
    return *m_ptcl;
}

coordinates_t Particle::getParticleCoordinates() const noexcept { return createCoordinates(
    m_ptcl->m_coordinates.x,
    m_ptcl->m_coordinates.y,
    m_ptcl->m_coordinates.z); }

bool Particle::intersectsSurface(ISurface const &surface) const
{
    return surface.intersectsSurface(createCoordinates(m_ptcl->m_coordinates.x,
                                                       m_ptcl->m_coordinates.y,
                                                       m_ptcl->m_coordinates.z));
}

void Particle::handleIntersection(ISurface const &surface, std::string_view filename)
{
    // Check if particle intersects with specified surface
    if (not intersectsSurface(surface))
        return;

    // Recording the coordinates to the log file
    prvt_record_intersection(getParticleCoordinates(), filename);

    // Finishing tracking equals to destroy object
    prvt_destroy();
}

Particle Particle::createRandomParticleOnSimpleSurface(ISurface const &surface,
                                                       coordinates_t const &min,
                                                       coordinates_t const &max)
{
    RealNumberGenerator rng;

    // ! Bad approach -> Interface exists, but need to specify separate methods for different types of surfaces !
    SimpleSurface const &simpleSurface{dynamic_cast<SimpleSurface const &>(surface)};

    Particle randomParticle;
    do
    {
        double randFixedX{rng.generateRandomNumber(min.x, max.x)},
            randFixedY{rng.generateRandomNumber(min.y, max.y)},
            // Solving `z` by using the plane equation Ax + By + Cz + D = 0:
            // z = (-Ax - By - D) / C
            z{(-simpleSurface.getA() * randFixedX - simpleSurface.getB() * randFixedY - simpleSurface.getD()) /
              simpleSurface.getC()};

        randomParticle.data().m_coordinates.x = randFixedX;
        randomParticle.data().m_coordinates.y = randFixedY;
        randomParticle.data().m_coordinates.z = z;
#ifdef DEBUG
        std::cout << std::format("({}*{})+({}*{})+({})/{}\n", -simpleSurface.getA(), randFixedX,
                                 -simpleSurface.getB(), randFixedY, -simpleSurface.getD(),
                                 simpleSurface.getC());
        std::cout << std::boolalpha << std::format("{},{},{} = {}\n", randFixedX, randFixedY, z, simpleSurface.intersectsSurface(randomParticle.getParticleCoordinates()));
#endif // !DEBUG
    } while (not simpleSurface.intersectsSurface(randomParticle.getParticleCoordinates()));

    return Particle(randomParticle);
}
