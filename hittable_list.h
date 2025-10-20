/*this is a class that stores a list of generic objects that the ray can intersect with 
it behaves like one big hitttable object and allows the ray tracer to render a full scene
Returns true if anything was hit
Returns false otherwise */

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "main.h"

#include <vector>


class hittable_list : public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects; //a vector of shared pointers to hittable objects

        hittable_list() {}
        hittable_list(shared_ptr<hittable>object) { add(object); }

        void clear() { objects.clear(); } //remove all obects from the list

        //append a new object to the list
        void add(shared_ptr<hittable> object) {
            objects.push_back(object);
        }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override{
            hit_record temp_rec; //temp record for each object tested
            bool hit_anything = false;
            auto closest_so_far = ray_t.max;

            //each object is a pointer to a hittable shape
            for (const auto& object : objects) {
                /*call each object's hit() function. 
                If the ray hits the object and is closer than a previous hit, 
                then record and update the closest hit*/
                if(object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }//end for

            return hit_anything;
        }
};

#endif