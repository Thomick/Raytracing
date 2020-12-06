#ifndef VEC3_H
#define VEC3_H

#include "Utilities.hpp"

class Vec3
{
public:
    Vec3() : v{0, 0, 0} {}
    Vec3(double v0, double v1, double v2) : v{v0, v1, v2} {}

    double x() { return v[0]; }
    double y() { return v[1]; }
    double z() { return v[2]; }

    Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }
    double operator[](int i) const { return v[i]; }
    double &operator[](int i) { return v[i]; }

    Vec3 &operator+=(const Vec3 &other)
    {
        v[0] += other[0];
        v[1] += other[1];
        v[2] += other[2];
        return *this;
    }
    Vec3 &operator-=(const Vec3 &other)
    {
        return *this += -other;
    }
    Vec3 &operator*=(const double k)
    {
        v[0] *= k;
        v[1] *= k;
        v[2] *= k;
        return *this;
    }
    Vec3 &operator/=(const double k)
    {
        return *this *= 1 / k;
    }
    double length() const
    {
        return sqrt(length_squared());
    }
    double length_squared() const
    {
        return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    }
    bool near_zero()
    {
        const double eps = 1e-8;
        return fabs(v[0]) < eps && fabs(v[1]) < eps && fabs(v[2]) < eps;
    }

    inline static Vec3 random() { return Vec3(random_double(), random_double(), random_double()); }
    inline static Vec3 random(double min, double max) { return Vec3(random_double(min, max), random_double(min, max), random_double(min, max)); }

private:
    double v[3];
};

// Aliases
using Point3 = Vec3;
using Color = Vec3;

// Vec3 operators
inline std::ostream &operator<<(std::ostream &out, const Vec3 &v)
{
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}
inline Vec3 operator+(const Vec3 &a, const Vec3 &b)
{
    return Vec3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}
inline Vec3 operator-(const Vec3 &a, const Vec3 &b)
{
    return a + -b;
}
inline Vec3 operator*(double k, const Vec3 &v)
{
    return Vec3(k * v[0], k * v[1], k * v[2]);
}
inline Vec3 operator*(const Vec3 &v, double k)
{
    return k * v;
}
inline Vec3 operator*(const Vec3 &a, const Vec3 &b)
{
    return Vec3(a[0] * b[0], a[1] * b[1], a[2] * b[2]);
}
inline Vec3 operator/(const Vec3 &v, double k)
{
    return (1 / k) * v;
}
inline double dot(const Vec3 &a, const Vec3 &b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
inline Vec3 cross(const Vec3 &a, const Vec3 &b)
{
    Vec3 cp;
    cp[0] = a[1] * b[2] - a[2] * b[1];
    cp[1] = a[2] * b[0] - a[0] * b[2];
    cp[2] = a[0] * b[1] - a[1] * b[0];
    return cp;
}
inline Vec3 unit_vector(const Vec3 &v)
{
    return v / v.length();
}
Vec3 random_in_unit_sphere()
{
    while (true)
    {
        Vec3 p = Vec3::random();
        if (p.length_squared() <= 1)
            return p;
    }
}
Vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}
Vec3 random_in_hemisphere(const Vec3 &base)
{
    Vec3 res = random_unit_vector();
    if (dot(base, res) < 0)
        return -res;
    return res;
}
Vec3 reflect(const Vec3 &v, const Vec3 &n) { return v - 2 * dot(v, n) * n; }
Vec3 refract(const Vec3 &uv, const Vec3 &n, double ni_over_nt) // uv is a unit vector
{                                                              // ni_over_nt indice of the incident material over ind of the material in which the ray is transmited
    double costheta = fmin(dot(uv, n), 1.0);
    Vec3 perpendicular = ni_over_nt * (uv - costheta * n);
    Vec3 parallel = -sqrt(fabs(1 - perpendicular.length_squared())) * n;
    return perpendicular + parallel;
}

#endif // !VEC3_H