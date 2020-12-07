#include <iostream>
#include "Utilities.hpp"
#include "Color.hpp"
#include "Hittable_list.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Space_sampling.hpp"

void generate_random_spherefield(const Point3 &origin, const Vec3 &field_size, double min_dist, double radius, Hittable_list &scene)
{
    vector<Point3> ball_pos;
    poisson_sphere_sampling(origin, field_size, min_dist, ball_pos);
    for (auto pos : ball_pos)
    {
        double rand_mat = random_double();
        Color rand_color = Color::random();
        if (rand_mat < 0.6)
        {
            auto mat = make_shared<Lambertian>(rand_color);
            scene.add(make_shared<Sphere>(pos, radius, mat));
        }
        else if (rand_mat < 0.8)
        {
            double rand_fuzz = random_double();
            auto mat = make_shared<Metal>(rand_color, rand_fuzz);
            scene.add(make_shared<Sphere>(pos, radius, mat));
        }
        else if (rand_mat < 0.9)
        {
            double rand_fuzz = random_double();
            auto mat = make_shared<Dielectric>(rand_color, 1.5, rand_fuzz);
            scene.add(make_shared<Sphere>(pos, radius, mat));
        }
        else
        {
            double rand_fuzz = random_double();
            auto mat = make_shared<Dielectric>(rand_color, 1.5, rand_fuzz);
            scene.add(make_shared<Sphere>(pos, radius, mat));
            scene.add(make_shared<Sphere>(pos, -(radius - 0.1), mat));
        }
    }
}

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
    const int sample_per_pixel = 100;
    const int max_depth = 50;

    //Camera
    Point3 look_from(0, 0, 0);
    Point3 look_at(0, 0, -1);
    Vec3 vup(0, 1, 0);
    double vfov = 90;
    double aperture = 0;
    double focus_dist = 1;
    Camera camera(look_from, look_at, vup, aspect_ratio, vfov, aperture, focus_dist);

    // Scene
    Hittable_list scene;
    generate_random_spherefield(Point3(-7, -7, -5), Vec3(14, 14, 7), 2, 0.5, scene);

    std::cout
        << "P3" << std::endl
        << im_width << ' ' << im_height << std::endl
        << 255 << std::endl;

    for (int i = im_height - 1; i >= 0; i--)
    {
        if (i % 1 == 0)
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
