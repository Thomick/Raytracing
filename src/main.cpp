#include <iostream>
#include "Utilities.hpp"
#include "Color.hpp"
#include "Hittable_list.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Material.hpp"

Color ray_color(const Ray &r, const Hittable_list &scene, int depth)
{
    if (depth <= 0)
        return Color(0, 0, 0);
    hit_record hrec;
    if (scene.hit(r, 0.0001, infinity, hrec)) // 0.0001 avoids hitting the same object multiple times due to floating point approximation
    {
        Color attenuation;
        Ray scattered_ray;
        if (hrec.mat_ptr->scatter(r, hrec, attenuation, scattered_ray))
            return attenuation * ray_color(scattered_ray, scene, depth - 1);
        return Color(0, 0, 0);
    }
    Vec3 unit_dir = unit_vector(r.getDirection());
    double t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * (Color(1, 1, 1)) + t * Color(0.2, 0.3, 1);
}

int main()
{
    //Image size
    const double aspect_ratio = 16.0 / 9.0;
    const int im_width = 400;
    const int im_height = (int)(im_width / aspect_ratio);
    const int sample_per_pixel = 500;
    const int max_depth = 50;

    //Camera
    Camera camera;

    // Scene
    Hittable_list scene;
    auto material_ground = make_shared<Lambertian>(Color(0.3, 0.9, 0.3));
    auto material_center = make_shared<Lambertian>(Color(1, 0, 0));
    auto material_left = make_shared<Metal>(Color(0.5, 0.3, 0.7));
    auto material_right = make_shared<Metal>(Color(1, 1, 0.2));

    scene.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5, material_center));
    scene.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100, material_ground));
    scene.add(make_shared<Sphere>(Point3(-2, 0, -2), 0.5, material_left));
    scene.add(make_shared<Sphere>(Point3(1, 0, -1), 0.5, material_right));

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