#include <iostream>
#include "Utilities.hpp"
#include "Color.hpp"
#include "Hittable_list.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"

Color ray_color(const Ray &r, const Hittable_list &scene, int depth)
{
    if (depth <= 0)
        return Color(0, 0, 0);
    hit_record hrec;
    if (scene.hit(r, 0.0001, infinity, hrec)) // 0.0001 avoids hitting the same object multiple times due to floating point approximation
    {
        Vec3 new_dir = hrec.normal + random_unit_vector(); // Lambertian distribution
        //Vec3 new_dir = random_in_hemisphere(hrec.normal); // Uniform distribution
        return 0.5 * ray_color(Ray(hrec.p, new_dir), scene, depth - 1);
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
    const int sample_per_pixel = 100;
    const int max_depth = 50;

    //Camera
    Camera camera;

    // Scene
    Hittable_list scene;
    scene.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    scene.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    std::cout
        << "P3" << std::endl
        << im_width << ' ' << im_height << std::endl
        << 255 << std::endl;

    for (int i = im_height - 1; i >= 0; i--)
    {
        if (i % 20 == 0)
            std::cerr << i << " lines remaining -> " << (1 - (double)i / im_height) * 100 << "%" << std::endl;
        for (int j = 0; j < im_width; j++)
        {
            Color pixel_color(0, 0, 0);
            for (int k = 0; k < sample_per_pixel; k++)
            {
                double v = (i + random_double()) / im_height;
                double u = (j + random_double()) / im_width;
                pixel_color += ray_color(camera.get_ray(u, v), scene, max_depth);
            }
            write_color(std::cout, pixel_color, sample_per_pixel);
        }
    }
    std::cerr << "Image generated !" << std::endl;
}