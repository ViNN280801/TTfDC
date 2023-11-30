#include "../include/surface.hpp"

SimpleSurface::SimpleSurface(double A, double B, double C, double D)
    : m_A(A), m_B(B), m_C(C), m_D(D) {}

bool SimpleSurface::intersectsSurface(coordinates_t const &coordinates) const
{
    return m_A * coordinates.x + m_B * coordinates.y + m_C * coordinates.z + m_D == 0.0;
}
