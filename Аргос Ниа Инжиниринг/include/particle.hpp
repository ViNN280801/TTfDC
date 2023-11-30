#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <memory>
#include <string_view>
#include <ostream>

#include "../include/surface.hpp"

class Particle
{
private:
    /// @brief Implementation of the `Particle` class (structs of the params there).
    struct ParticleImpl;
    std::unique_ptr<ParticleImpl> m_ptcl; // Ptr to the implementation struct.

    /**
     * @brief Copies all data from `other` to the current `Particle` instance.
     * Copies with little difference (epsilon for correspoding type).
     * ! Weight, velocity and charge don't changed. Changes only position. !
     * @param other `Particle` instance to copy content from it.
     */
    void prvt_copy(Particle const &other);

    /**
     * @brief Records intersection in format "{} {} {}\n".
     * @param coordinates Cartesian coordinates.
     * @param filename Name of the file to do records.
     */
    void prvt_record_intersection(coordinates_t const &coordinates, std::string_view filename) const;

    /// @brief Destoys current `Particle` object.
    void prvt_destroy();

public:
    /// @brief Ctor.
    explicit Particle();

    /*  If we considering ability of the copy all characteristics from one   */
    /*  particle to another, it might be reasonable, but I don't think that  */
    /*  in the real life may be two different particles with the same state. */
    /* Basing on these considerations we'll copy particles with little diff. */
    /// @brief Copy ctor.
    explicit Particle(Particle const &other);
    /// @brief Copy-assignment operator.
    Particle &operator=(Particle const &other);

    /* Restrict to move the particles, because in real life particles */
    /* can't transfer their state and properties to another particles. */
    /// @brief Deleted move-ctor.
    explicit Particle(Particle &&) noexcept = delete;
    /// @brief Deleted move-assignment operator.
    Particle &operator=(Particle &&) noexcept = delete;

    /**
     * @brief Comparing less operator.
     * @param lhs Left-hand-side `Particle` object.
     * @param rhs Right-hand-side `Particle` object.
     * @return `true` if at least on of the params
     * of the particle in `lhs` < the same param in `rhs`, otherwise `false`.
     */
    friend bool operator<(Particle const &lhs, Particle const &rhs);

    /**
     * @brief Comparing greater operator.
     * @param lhs Left-hand-side `Particle` object.
     * @param rhs Right-hand-side `Particle` object.
     * @return `true` if at least on of the params
     * of the particle in `lhs` > the same param in `rhs`, otherwise `false`.
     */
    friend bool operator>(Particle const &lhs, Particle const &rhs);

    /**
     * @brief Comparing less operator.
     * @param lhs Left-hand-side `Particle` object.
     * @param rhs Right-hand-side `Particle` object.
     * @return `true` if at least on of the params
     * of the particle in `lhs` <= the same param in `rhs`, otherwise `false`.
     */
    friend bool operator<=(Particle const &lhs, Particle const &rhs);

    /**
     * @brief Comparing greater operator.
     * @param lhs Left-hand-side `Particle` object.
     * @param rhs Right-hand-side `Particle` object.
     * @return `true` if at least on of the params
     * of the particle in `lhs` >= the same param in `rhs`, otherwise `false`.
     */
    friend bool operator>=(Particle const &lhs, Particle const &rhs);

    /**
     * @brief Comparing on equality operator.
     * @param lhs Left-hand-side `Particle` object.
     * @param rhs Right-hand-side `Particle` object.
     * @return `true` if `Particle`s are equal, otherwise `false`.
     */
    friend bool operator==(Particle const &lhs, Particle const &rhs);

    /**
     * @brief Comparing on equality operator.
     * @param lhs Left-hand-side `Particle` object.
     * @param rhs Right-hand-side `Particle` object.
     * @return `true` if `Particle`s aren't equal, otherwise `false`.
     */
    friend bool operator!=(Particle const &lhs, Particle const &rhs);

    friend std::ostream &operator<<(std::ostream &os, Particle const &particle);

    /// @brief Dtor.
    virtual ~Particle();

    /// @brief Prints to the `stdout` all info about the current particle.
    void printData() const noexcept;

    /// @brief Getter for underlying object of the `Particle`.
    ParticleImpl &data() noexcept(false);

    /// @brief Getter fot the coordinates of the particle.
    coordinates_t getParticleCoordinates() const noexcept;

    /**
     * @brief Checks if the particle intersects with a given surface.
     * @param surface The surface to check intersection with.
     * @return true if the particle intersects with the surface, false otherwise.
     */
    bool intersectsSurface(ISurface const &surface) const;

    /**
     * @brief Handles the intersection of the particle with a given surface.
     * Stops tracking the particle and records the intersection.
     * @param surface The surface with which the particle may intersect.
     * @param filename Name of the file to do records.
     */
    void handleIntersection(ISurface const &surface, std::string_view filename);

    /**
     * @brief Creates a new particle randomly on a specified simple surface within given coordinate ranges.
     * @param surface The surface where to create particle.
     * @param min The minimum coordinates (x, y, z) to restrict the particle's position.
     * @param max The maximum coordinates (x, y, z) to restrict the particle's position.
     * @return A new Particle instance randomly generated on the surface within the specified coordinate ranges.
     */
    static Particle createRandomParticleOnSimpleSurface(ISurface const &surface,
                                                        coordinates_t const &min = kdefault_min_coordinates,
                                                        coordinates_t const &max = kdefault_max_coordinates);
};

#endif // !PARTICLE_HPP
