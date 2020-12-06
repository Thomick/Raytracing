#ifndef COLOR_H
#define COLOR_H

#include "Vec3.hpp"
#include "Utilities.hpp"
using Color = Vec3;

void write_color(std::ostream &out, Color &color, int sample_per_pixel)
{
    // Scale the color to the correct range and gamma correction (gamma=2)
    double scale = 1.0 / sample_per_pixel;
    double r = sqrt(color.x() * scale);
    double g = sqrt(color.y() * scale);
    double b = sqrt(color.z() * scale);

    out << (int)clamp(r * 256, 0, 255) << ' ' << (int)clamp(g * 256, 0, 255) << ' ' << (int)clamp(b * 256, 0, 255) << std::endl;
}

#endif // !COLOR_H