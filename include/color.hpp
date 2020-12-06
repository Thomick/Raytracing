#ifndef COLOR_H
#define COLOR_H

#include "Vec3.hpp"
using Color = Vec3;

void write_color(std::ostream &out, Color &color, int sample_per_pixel)
{
    double scale = 256.0 / sample_per_pixel;
    int r = (int)clamp(color.x() * scale, 0, 255);
    int g = (int)clamp(color.y() * scale, 0, 255);
    int b = (int)clamp(color.z() * scale, 0, 255);

    out << r << ' ' << g << ' ' << b << std::endl;
}

#endif // !COLOR_H