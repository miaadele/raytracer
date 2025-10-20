/*This file will:
Set up a simple camera
    Set up the pixel dimensions for the rendered image
    Set up a virtual viewp;ort
    Define the camera center / eye point
    Set the focal length
    Scan the image

Produce a linear gradient
*/

#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

/*
create a linear gradient by blending 2 colors
this forms a linear interpolation, referred to as a lerp between two values
*/
color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main(){

    auto aspect_ratio = 16.0 / 9.0;
    int img_width = 400;
    int img_height = int(img_width / aspect_ratio);
    if (img_height < 1) {
        img_height = 1;
    }

    //Set up camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(img_width)/img_height);
    auto camera_center = point3(0,0,0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / img_width;
    auto pixel_delta_v = viewport_v / img_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    //Render
    std:: cout << "P3\n" << img_width << " " << img_height << "\n255\n";

    for (int j = 0; j < img_height; j++) {
        //process indicator to track rendering progress:
        std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' <<std::flush;
        for (int i = 0; i < img_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone. \n";
}