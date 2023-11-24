#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "rtweekend.h"

class camera {
public:
    double aspect_ratio = 1.0;
    int image_width = 100;

    void render(hittable_list&world) {
        // Initialise before render.
        init();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int i = 0; i < image_height; i++) {
            std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
            for (int j = 0; j < image_width; j++) {
                auto pixel_center = pixel00_loc + (j * pixel_delta_u) + (i * pixel_delta_v);
                auto ray_direction = pixel_center - camera_center;
                ray r(camera_center, ray_direction);

                color pixel_color = ray_color(world, r);
                write_color(std::cout, pixel_color);
            }
        }

        std::clog << "\rDone.   \n";
    }

private:
    int image_height;
    point3 pixel00_loc;
    point3 camera_center;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    void init() {
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = image_height < 1 ? 1 : image_height;


        camera_center = point3(0, 0, 0);

        // Determine viewport dimensions.
        auto focal_length = vec3(0, 0, 1);
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (
                                  static_cast<double>(image_width) / image_height);

        // Calculate horizontal and vertical vectors across viewport.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate location of upper left pixel.
        auto viewport_upper_left = camera_center - focal_length - viewport_u / 2 - viewport_v /
                                   2;
        pixel00_loc = viewport_upper_left + (0.5 * (pixel_delta_u + pixel_delta_v));
    }

    color ray_color(const hittable&world, const ray&r) const {
        hit_record rec;

        if (world.hit(r, interval(0, infinity), rec)) {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};

#endif //CAMERA_H
