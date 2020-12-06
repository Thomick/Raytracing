#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) { return degrees * pi / 180; }

inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

// Random
inline double random_double() //random double in [0,1)
{
    return rand() / (RAND_MAX + 1.0);
}
inline double random_double(double min, double max)
{
    return min + random_double() * (max - min);
}

#include "Vec3.hpp"
#include "Ray.hpp"

#endif // !UTILITIES_H
