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
        Vec3 scatter_dir = hrec.normal + random_unit_vector(); // Lambertian distribution
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
    double fuzz;

public:
    Metal(const Color &albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
    virtual bool scatter(const Ray &ray_in, const hit_record &hrec, Color &attenuation, Ray &ray_scattered) const override
    {
        attenuation = albedo;
        Vec3 scatter_dir = reflect(unit_vector(ray_in.getDirection()), hrec.normal) + fuzz * random_unit_vector();
        ray_scattered = Ray(hrec.p, scatter_dir);
        return dot(scatter_dir, hrec.normal) > 0;
    }
};

class Dielectric : public Material
{
private:
    Color albedo;
    double ir; // Index of refraction
    double fuzz;

public:
    Dielectric(const Color &albedo, double ir, double fuzz = 0) : albedo(albedo), ir(ir), fuzz(fuzz) {}
    virtual bool scatter(const Ray &ray_in, const hit_record &hrec, Color &attenuation, Ray &ray_scattered) const override
    {
        attenuation = albedo;
        double refraction_ratio = hrec.front_face ? (1.0 / ir) : ir;
        Vec3 unit_direction = unit_vector(ray_in.getDirection());
        double costheta = fmin(dot(-unit_direction, hrec.normal), 1.0);
        double sintheta = sqrt(1 - costheta * costheta);
        Vec3 scatter_dir;
        if (sintheta * refraction_ratio > 1.0 || reflectance(costheta, refraction_ratio) > random_double())
            scatter_dir = reflect(unit_direction, hrec.normal);
        else
            scatter_dir = refract(unit_direction, hrec.normal, refraction_ratio) + fuzz * random_unit_vector();
        ray_scattered = Ray(hrec.p, scatter_dir);
        return true;
    }

private:
    static double reflectance(double cosine, double refraction_ratio) // Schlick's approximation
    {
        double r0 = (1 - refraction_ratio) / (1 + refraction_ratio);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};

#endif // !MATERIAL_H