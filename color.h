#ifndef COLOR_H
#define COLOR_H
#include "vec3.h"

using colour = vec3;

inline void write_colour(std::ostream &out, const colour &pixel_colour) {
    out << (static_cast<int>(255.99 * pixel_colour.x())) << ' '
    << (static_cast<int>(255.99 * pixel_colour.y())) << ' '
    << (static_cast<int>(255.99 * pixel_colour.z())) << '\n';
}

#endif //COLOR_H
