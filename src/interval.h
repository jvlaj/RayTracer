#ifndef INTERVAL_H
#define INTERVAL_H
#include "rtweekend.h"

class interval {
public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {
    } // Default interval is empty

    interval(double _min, double _max) : min(_min), max(_max) {
    }

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    static const interval empty, universe;
};

const interval empty(+infinity, -infinity);
const interval universe(-infinity, +infinity);

#endif //INTERVAL_H