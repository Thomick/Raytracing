#ifndef CAMERA_H
#define CAMERA_H

#include "Utilities.hpp"

class Camera
{
private:
    Point3 origin;
    Vec3 horizontal;
    Vec3 vertical;
    Point3 lower_left_corner;
    Vec3 u, v, w;
    double lens_radius;

public:
    Camera(const Point3 &look_from, const Point3 &look_at, const Vec3 &vup, double aspect_ratio, double vfov, double aperture, double focus_dist) // vfov = vertical fied of view, vup = view up
    {
        double theta = degrees_to_radians(vfov);
        double h = tan(theta / 2);
        double viewport_height = 2.0 * h;
        double viewport_width = viewport_height * aspect_ratio;

        w = unit_vector(look_from - look_at);
        u = unit_vector(cross(vup, w));
        v = unit_vector(cross(w, u));

        origin = look_from;
        vertical = focus_dist * viewport_height * v;
        horizontal = focus_dist * viewport_width * u;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

        lens_radius = aperture / 2;
    }

    Ray get_ray(double hpos, double vpos)
    {
        Vec3 random_disk = lens_radius * random_in_unit_disk();

        Vec3 offset = random_disk.x() * u + random_disk.y() * v;

        return Ray(origin + offset, lower_left_corner + hpos * horizontal + vpos * vertical - origin - offset);
    }
};

#endif // !CAMERA_H
