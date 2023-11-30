#ifndef COORDINATES_HPP
#define COORDINATES_HPP

static constexpr double kdefault_pos{0.0};

/// @brief Cartesian coordinates (x, y, z).
struct coordinates_t
{
    double x{kdefault_pos};
    double y{kdefault_pos};
    double z{kdefault_pos};

    /// @brief Ctor.
    coordinates_t() {}

    /// @brief Ctor with params
    coordinates_t(double new_x, double new_y, double new_z)
    {
        x = new_x;
        y = new_y;
        z = new_z;
    }
};

static const coordinates_t kdefault_min_coordinates{-10.0, -10.0, -10.0};
static const coordinates_t kdefault_max_coordinates{10.0, 10.0, 10.0};

/**
 * @brief Fills `coordinates_t` structure with specified values.
 * @param x X-coordinate of the point.
 * @param y Y-coordinate of the point.
 * @param z Z-coordinate of the point.
 * @return Filled structure of the Cartesian coordinates.
 */
coordinates_t createCoordinates(double x, double y, double z);

#endif // !COORDINATES_HPP
