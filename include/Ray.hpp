#ifndef RAY_H
#define RAY_H

#include "Vec3.hpp"

class Ray
{
public:
    Ray() {}
    Ray(Point3 &origin, Vec3 &dir) : origin(origin), dir(dir) {}

    Point3 getOrigin() const { return origin; }
    Vec3 getDirection() const { return dir; }

    Point3 at(double t) const { return origin + t * dir; }

private:
    Point3 origin;
    Vec3 dir;
};

#endif // !RAY_H