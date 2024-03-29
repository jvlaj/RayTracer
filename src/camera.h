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
    int samples_per_pixel = 10;
    int max_depth = 10;

    double defocus_angle = 0; // Variation anggle of rays through each pixel.
    double focus_dist = 10; // Distance from  camera lookfrom point to plane of perfect focus.

    double fov = 90; // Vertical view angle (field of view)

    point3 look_from = point3(0,0,-1); // Point camera is looking from
    point3 look_at = point3(0,0,0); // Point camera is looking at
    vec3 vup = vec3(0,1,0); // Camera-relative "up" direction

    void render(hittable_list&world) {
        // Initialise before render.
        init();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int i = 0; i < image_height; i++) {
            std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
            for (int j = 0; j < image_width; j++) {
                color pixel_color(0,0,0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i,j);
                    pixel_color += ray_color(world, r, max_depth);
                }
                write_color(std::cout, pixel_color, samples_per_pixel);
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
    vec3 u, v, w; // Camera frame basis vectors
    vec3 defocus_disk_u; // Defocus disk horizontal radius
    vec3 defocus_disk_v; // Defocus disk vertical radius

    void init() {
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = image_height < 1 ? 1 : image_height;

        camera_center = look_from;

        // Determine viewport dimensions.
        auto theta = degree_to_radians(fov);
        auto h = tan(theta/2);
        double viewport_height = 2 * h  * focus_dist;
        double viewport_width = viewport_height * (
                                    static_cast<double>(image_width) / image_height);

        // Calculate the u,v,w unit basis viectors for the camera coord frame
        w = unit_vector(look_from - look_at);
        u = unit_vector(cross(vup, w));
        v = cross(w,u);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        vec3 viewport_u = viewport_width * u;
        vec3 viewport_v = viewport_height * -v;

        // Calculate horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate location of upper left pixel.
        auto viewport_upper_left = camera_center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + (0.5 * (pixel_delta_u + pixel_delta_v));

        // Calculate the camera defocus disk basis vectors
        auto defocus_radius = focus_dist *  tan(degree_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;

    }

    color ray_color(const hittable&world, const ray&r, int depth) const {
        hit_record rec;

        if (depth <= 0)
            return color(0,0,0);

        if (world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(world, scattered, depth-1);
            return color(0,0,0);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }

    ray get_ray(int i, int j) const {
        //Get a randomly sampled camera ray for the pixel at location i,j,
        //originating from the camera defocus disk.

        auto pixel_center = pixel00_loc + (j * pixel_delta_u) + (i * pixel_delta_v);
        auto pixel_sample = pixel_center + pixel_sample_square();

        auto ray_origin = (defocus_angle <= 0) ? camera_center : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    point3 defocus_disk_sample() const {
        // Returns a random point in the camera defocus disk.

        auto p = random_in_unit_disc();
        return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    vec3 pixel_sample_square() const {
        // Returns a random point in the square surrounding a pixel at the origin.

        auto px = -0.5 + random_double();
        auto py = -0.5 + random_double();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }
};

#endif //CAMERA_H
