#ifndef COLOR_H
#define COLOR_H
#include "vec3.h"

using color = vec3;

inline void write_color(std::ostream &out, const color &pixel_color) {
    out << (static_cast<int>(255.99 * pixel_color.x())) << ' '
    << (static_cast<int>(255.99 * pixel_color.y())) << ' '
    << (static_cast<int>(255.99 * pixel_color.z())) << '\n';
}

#endif //COLOR_H
