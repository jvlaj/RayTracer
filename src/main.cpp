#include "camera.h"
#include "memory"

int main() {
    // World
    hittable_list world;

    // Objects
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;

    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 400;

    cam.render(world);
}