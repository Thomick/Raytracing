#include <iostream>
#include "Utilities.hpp"
#include "Color.hpp"
#include "Hittable_list.hpp"
#include "Sphere.hpp"

Color ray_color(Ray &r, const Hittable_list &scene)
{
    hit_record hrec;
    if (scene.hit(r, 0, infinity, hrec))
    {
        return 0.5 * (hrec.normal + Color(1, 1, 1));
    }
    Vec3 unit_dir = unit_vector(r.getDirection());
    double t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * (Color(1, 1, 1)) + t * Color(0.5, 0.8, 0.3);
}

int main()
{
    //Image size
    const double aspect_ratio = 16.0 / 9.0;
    const int im_width = 400;
    const int im_height = (int)(im_width / aspect_ratio);

    // Scene
    Hittable_list scene;
    scene.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    scene.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera and viewport
    double viewport_height = 2;
    double viewport_width = viewport_height * aspect_ratio;
    double focal_length = 1;

    Point3 origin = Point3(0, 0, 0);
    Vec3 vertical = Vec3(0, viewport_height, 0);
    Vec3 horizontal = Vec3(viewport_width, 0, 0);
    Point3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);

    std::cout
        << "P3" << std::endl
        << im_width << ' ' << im_height << std::endl
        << 255 << std::endl;

    for (int i = im_height - 1; i >= 0; i--)
    {
        if (i % 50 == 0)
            std::cerr << i << " lines remaining -> " << (1 - (double)i / im_height) * 100 << "%" << std::endl;
        for (int j = 0; j < im_width; j++)
        {
            double v = (double)(i) / im_height;
            double u = (double)(j) / im_width;
            Vec3 dir = lower_left_corner + v * vertical + u * horizontal;
            Ray r(origin, dir);
            Color pix_color = ray_color(r, scene);
            write_color(std::cout, pix_color);
        }
    }
    std::cerr << "Image generated !" << std::endl;
}