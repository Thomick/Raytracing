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

public:
    Camera()
    {
        double aspect_ratio = 16.0 / 9.0;
        double viewport_height = 2;
        double viewport_width = viewport_height * aspect_ratio;
        double focal_length = 1;

        origin = Point3(0, 0, 0);
        vertical = Vec3(0, viewport_height, 0);
        horizontal = Vec3(viewport_width, 0, 0);
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);
    }

    Ray get_ray(double u, double v)
    {
        return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }
};

#endif // !CAMERA_H
