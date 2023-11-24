#ifndef RTWEEKEND_H
#define RTWEEKEND_H
#include <memory>
#include <cmath>
#include <vector>

// Usings

using std::vector;
using std::sqrt;
using std::make_shared;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degree_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Common Headers

#include "interval.h"
#include "ray.h"
#include "vec3.h"


#endif //RTWEEKEND_H
