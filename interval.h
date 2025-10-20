/*this class manages real-valued intervals with a min and max*/
#ifndef INTERVAL_H
#define INTERVAL_H

#include "main.h"

class interval {
  public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    interval(double min, double max) : min(min), max(max) {}

    double size() const {
        return max - min;
    }

    bool contains(double x) const{
            if(min <= x && x <= max) {
                return true;
            } else {
                return false;
            }
        }

        bool surrounds(double x) const {
            if(min < x && x < max) {
                return true;
            } else {
                return false;
            }
        }

    static const interval empty, universe;
};

const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif