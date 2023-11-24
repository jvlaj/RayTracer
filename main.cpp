#include <iostream>
#include "rtweekend.h"
#include <stb/stb_image.h>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"
#include "hittable_list.h"

colour ray_colour(const hittable &world, const ray& r) {

    hit_record rec;

    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + colour(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-a) * colour(1.0, 1.0, 1.0) + a * colour(0.5, 0.7, 1.0);
}

int main() {

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Image
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    // World

    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Viewport
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

    // camera
    auto camera_center = point3(0,0,0);
    auto focal_length = vec3(0,0,1);

    // calculate the horizontal and vertical vectors across the viewport
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // horizontal and vertical vectors from pixel to pixel
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // calculate location  of upper left pixel
    auto viewport_upper_left = camera_center - focal_length - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + (0.5 * (pixel_delta_u + pixel_delta_v));

    std::cout << "P3\n" <<  image_width << ' ' << image_height << "\n255\n";

    // sphere

    sphere s1(point3(0,0,-1), 0.5);

     for(int i = 0; i < image_height; i++) {
         std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
         for (int j = 0; j < image_width; j++) {
             auto pixel_center = pixel00_loc + (j * pixel_delta_u) + (i * pixel_delta_v);
             auto ray_direction = pixel_center - camera_center;
             ray r(camera_center, ray_direction);

             colour pixel_colour = ray_colour(world, r);
             write_colour(std::cout, pixel_colour);

         }
     }

    std::clog << "\rDone.   \n";

}