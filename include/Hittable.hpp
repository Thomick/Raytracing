#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.hpp"

struct hit_record
{
    Point3 p;
    Vec3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(const Ray &r, const Vec3 &outward_normal)
    {
        front_face = dot(r.getDirection(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable
{
public:
    virtual bool hit(const Ray &ray, double t_min, double t_max, hit_record &hrec) const = 0;
};

#endif // !HITTABLE_H