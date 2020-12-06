#ifndef MATERIAL_H
#define MATERIAL_H

#include "Utilities.hpp"
#include "Hittable.hpp"

class Material
{
public:
    virtual bool scatter(const Ray &ray_in, const hit_record &hrec, Color &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material
{
private:
    Color albedo;

public:
    Lambertian(const Color &a) : albedo(a) {}
    virtual bool scatter(const Ray &ray_in, const hit_record &hrec, Color &attenuation, Ray &ray_scattered) const override
    {
        attenuation = albedo;
        Vec3 scatter_dir = hrec.normal + random_in_unit_sphere(); // Lambertian distribution
        //Vec3 scatter_dir = random_in_hemisphere(hrec.normal); // Uniform distribution
        if (scatter_dir.near_zero()) // the two vectors cancel out
            scatter_dir = hrec.normal;
        ray_scattered = Ray(hrec.p, scatter_dir);
        return true;
    }
};

class Metal : public Material
{
private:
    Color albedo;

public:
    Metal(const Color &albedo) : albedo(albedo) {}
    virtual bool scatter(const Ray &ray_in, const hit_record &hrec, Color &attenuation, Ray &ray_scattered) const override
    {
        attenuation = albedo;
        Vec3 scatter_dir = reflect(ray_in.getDirection(), hrec.normal);
        ray_scattered = Ray(hrec.p, scatter_dir);
        return dot(scatter_dir, hrec.normal) > 0;
    }
};

#endif // !MATERIAL_H