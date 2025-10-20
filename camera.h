/* this class does 2 things:
1. construct and dispatch rays into the world
2. use the results of the rays to construct the rendered image
*/

#ifndef CAMERA_H
#define CAMERA_H

#include "main.h"
#include "hittable.h"

class camera{
    public:
        double aspect_ratio = 1.0; //ratio of image width over height
        int img_width = 100; //rendered image width in pixel count

        void render(const hittable& world) {
            intialize();
            
            //Render
            std:: cout << "P3\n" << img_width << " " << img_height << "\n255\n";

            for (int j = 0; j < img_height; j++) {
                //process indicator to track rendering progress:
                std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' <<std::flush;
                for (int i = 0; i < img_width; i++) {
                    auto pixel_center = px00_loc + (i * px_delta_u) + (j * px_delta_v);
                    auto ray_direction = pixel_center - center;
                    ray r(center, ray_direction);

                    color pixel_color = ray_color(r, world);
                    write_color(std::cout, pixel_color);
                }
            }
            std::clog << "\rDone. \n";
        }

    private: 
        int img_height; //rendered image height
        point3 center; //camera center
        point3 px00_loc; //location of pixel 0,0
        vec3 px_delta_u; //offset to pixel to the right
        vec3 px_delta_v; //offset to pixel below

        void intialize() {
            img_height = int(img_width / aspect_ratio);
            if (img_height < 1) {
                img_height = 1;
            }
            center = point3(0,0,0);

            //Set up camera
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(img_width)/img_height);

            // Calculate the vectors across the horizontal and down the vertical viewport edges.
            auto viewport_u = vec3(viewport_width, 0, 0);
            auto viewport_v = vec3(0, -viewport_height, 0);

            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            px_delta_u = viewport_u / img_width;
            px_delta_v = viewport_v / img_height;

            // Calculate the location of the upper left pixel.
            auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
            px00_loc= viewport_upper_left + 0.5 * (px_delta_u + px_delta_v);
        }

        color ray_color(const ray& r, const hittable& world) {
            hit_record rec;
            if(world.hit(r, interval(0, infinity), rec)) {
                return 0.5 * (rec.normal + color(1,1,1));
            }

            /* create a linear gradient by blending 2 colors
            this forms a linear interpolation, referred to as a lerp between two values */
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0 - a) * color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }
};

#endif