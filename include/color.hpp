#ifndef COLOR_H
#define COLOR_H

#include "Vec3.hpp"
using Color = Vec3;

void write_color(std::ostream &out, Color &color)
{
    out << static_cast<int>(255.999 * color[0]) << ' ' << static_cast<int>(255.999 * color[1]) << ' ' << static_cast<int>(255.999 * color[2]) << std::endl;
}

#endif // !COLOR_H