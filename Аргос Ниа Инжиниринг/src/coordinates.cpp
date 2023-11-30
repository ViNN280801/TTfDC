#include "../include/coordinates.hpp"

coordinates_t createCoordinates(double x, double y, double z)
{
    coordinates_t cords;

    cords.x = x;
    cords.y = y;
    cords.z = z;

    return cords;
}
