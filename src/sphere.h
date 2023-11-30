#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"
#include <cmath>
#include "material.h"

class sphere : public hittable {
public:
    sphere(point3 _centre, double _radius, shared_ptr<material> _material): centre(_centre), radius(_radius), mat(_material) {
    };

    bool hit(const ray&r, interval ray_t,
             hit_record&rec) const override {
        vec3 original_centre = r.origin() - centre;
        auto a = r.direction().length_squared();
        auto half_b = dot(original_centre, r.direction());
        auto c = original_centre.length_squared() - radius * radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false;

        auto sqrtd = sqrt(discriminant);

        // find the nearest root that lies in the acceptable range
        auto root = (-half_b - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (-half_b + sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                return false;
            }
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - centre) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;

        return true;
    }

private:
    point3 centre;
    double radius;
    shared_ptr<material>  mat;
};


#endif //SPHERE_H
