/*This is a class of things that a ray might hit
This class has a hit function that takes in a ray*/

#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record{
    public:
        point3 p; //the point in 3D space where the ray hit the object
        vec3 normal; //the surface normal at the hit point
        double t; //the parameter value t along the ray where the hit occurs
        bool front_face;

        /*assumption: the vector passed to the set_face_normal() function is of unit length*/
        void set_face_normal(const ray& r, const vec3& outward_normal) {
            front_face = dot(r.direction(), outward_normal) < 0;

            //ensure that the normal always points against the ray's direction (consistently faces outward)
            if (front_face) {
                normal = outward_normal;
            } else{
                normal = -outward_normal;
            }
        }
};

class hittable{
    public:
        virtual ~hittable() = default;

        /*parameters:
        (ray being tested for intersection, min. valid t, max. valid t, reference where the object will store hit details if intersection occurs)*/
        virtual bool hit(const ray&r, interval ray_t, hit_record& rec) const = 0;
};

#endif