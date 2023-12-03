# RayTracer
This is a ray tracing project, built following the [Ray Tracing in a Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) book.

![Final Render](https://notes.jvlaj.com/ox-hugo/_20231201_214741screenshot.png)

## Building

On Linux:
```
cmake .
make
```
The executable should be `RayTracer`.

On Windows:
```
cmake -G "Visual Studio 17"
cmake --build .
```

The exectuable should be `Debug\RayTracer.exe`.

## Run

The image is printed in [PPM format](https://en.wikipedia.org/wiki/Image_file_format#PPM,_PGM,_PBM,_and_PNM). You'll want to pipe it into a file using `>`, so you can view it with your image viewer.

For example:

`.\Debug\RayTracer.exe > image.ppm`

## Scene

Configurations can be made to `src/main.cpp` to create your unique scene.

### Objects

Introduce or remove `sphere`s of `lambertian`, `metal` or `dielectric` material:
```C++
auto material1 = make_shared<dielectric>(1.5);
world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
```

### Camera

There are a number of camera parameters that can be assigned:
```C++
camera cam;

cam.aspect_ratio      = 16.0 / 9.0;
cam.image_width       = 1200;
cam.samples_per_pixel = 10;
cam.max_depth         = 50;

cam.fov     = 20;
cam.look_from = point3(13,2,3);
cam.look_at   = point3(0,0,0);
cam.vup      = vec3(0,1,0);

cam.defocus_angle = 0.6;
cam.focus_dist    = 10.0;
```
