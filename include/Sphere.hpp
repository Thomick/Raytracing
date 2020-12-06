#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.hpp"
#include "Hittable.hpp"

class Sphere : public Hittable
{
private:
    Point3 center;
    double radius;

public:
    Sphere() : center(0, 0, 0), radius(0) {}
    Sphere(Point3 center, double radius) : center(center), radius(radius) {}

    virtual bool hit(const Ray &r, double t_min, double t_max, hit_record &hrec) const override;
};

bool Sphere::hit(const Ray &r, double t_min, double t_max, hit_record &hrec) const
{
    double a = r.getDirection().length_squared();
    Vec3 oc = r.getOrigin() - center;
    double b = dot(r.getDirection(), oc);
    double c = oc.length_squared() - radius * radius;
    double discrim = b * b - a * c;
    if (discrim < 0)
        return false;
    double sqrtd = sqrt(discrim);
    double t = (-b - sqrtd) / a;
    if (t < t_min || t > t_max)
    {
        t = (-b + sqrtd) / a;
        if (t < t_min || t > t_max)
            return false;
    }
    hrec.t = t;
    hrec.p = r.at(hrec.t);
    Vec3 outward_normal = (hrec.p - center) / radius;
    hrec.set_face_normal(r, outward_normal);
    return true;
}

#endif // !SPHERE_H