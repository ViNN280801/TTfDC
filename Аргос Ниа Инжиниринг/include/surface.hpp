#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "coordinates.hpp"

/// @brief Interface that represents mathematical surface in 3D space.
class ISurface
{
public:
    virtual bool intersectsSurface(coordinates_t const &coordinates) const = 0;
};

/**
 * @brief Represents a simple mathematical surface which is a flat surface.
 * Surface described with mathematical equation: Ax + By + Cz + D
 */
class SimpleSurface : public ISurface
{
private:
    /* Coefficients of the surface equation: Ax + By + Cz + D = 0. */
    double m_A;
    double m_B;
    double m_C;
    double m_D;

public:
    /// @brief Ctor with params.
    explicit SimpleSurface(double A, double B, double C, double D);

    /**
     * @brief Checks if a point with coordinates (x, y, z) lies on the surface.
     * @param coordinates {x, y, z} - coordinates of the point.
     * @return `true` if the point lies on the surface, otherwise `false`.
     */
    bool intersectsSurface(coordinates_t const &coordinates) const override;

    /* ==> Getter methods. <=== */
    constexpr double getA() const { return m_A; }
    constexpr double getB() const { return m_B; }
    constexpr double getC() const { return m_C; }
    constexpr double getD() const { return m_D; }
};

/* Here you can define your own surfaces: */
/* 1) Sphere                              */
/* 2) Quadric surface                     */
/* 3) Topological surface                 */
/* 4) ...                                 */
/* class Sphere : public ISurface { ... };*/

#endif // !SURFACE_HPP
