#ifndef MATERIAL_H
#define MATERIAL_H

#include <pstl/algorithm_fwd.h>

#include "camera.h"
#include "rtweekend.h"

class  hit_record;

class material
{
    public:

    virtual ~material() = default;

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenutation, ray &scattered) const = 0;
};

class lambertian: public material {
public:

    lambertian(const color& a) : albedo(a) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenutation, ray &scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenutation = albedo;
        return true;
    }

private:
    color albedo;

};

class metal: public material {
public:
    metal(const color &a, double f) : albedo(a), f( f < 1 ? f : 1) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenutation, ray& scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()),  rec.normal);
        scattered = ray(rec.p, reflected + f*random_unit_vector());
        attenutation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

private:
    color albedo;
    double f;
};
#endif //MATERIAL_H
