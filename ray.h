/*
This file defines a ray as a class

A ray can be represented by the function P(t) = A + tb, where
P is a 3D position along a line in 3D
A is the ray origin
b is the ray direection
t is the ray parameter
*/

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray{
    public:
        //default constructor: create an uninitialized ray
        ray() {} 

        //parameterized constructor: initialize a ray with a specific origin and direction
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        //accessors that return read-only references to the ray's internal data
        const point3& origin() const { return orig; }
        const vec3& direction() const { return dir; }

        //compute a point along the ray for a given parameter t
        point3 at(double t) const{
            return orig + t*dir;
        }

    private:
        point3 orig;
        vec3 dir;

};
#endif