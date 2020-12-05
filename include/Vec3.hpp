#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
using std::sqrt;

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

private:
    double v[3];
};

// Alias
using Point3 = Vec3;

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

#endif // !VEC3_H