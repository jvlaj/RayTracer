cmake_minimum_required(VERSION 3.27)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracer src/main.cpp
        src/vec3.h
        src/color.h
        src/ray.h
        src/hittable.h
        src/sphere.h
        src/hittable_list.h
        src/rtweekend.h
        src/interval.h
        src/camera.h)

