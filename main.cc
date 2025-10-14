//Generate and output an image in PPM format

#include "color.h"
#include "vec3.h"

#include <iostream>

int main(){

    //set image dimensions
    int img_width = 256;
    int img_height = 256;

    //output the PPM header
    std::cout <<"P3\n" << img_width << ' ' << img_height << "\n255\n";

    /*
    generate each pixel, row by row, left to right, from top to bottom
    R goes from black (0.0) to red (1.0) from left to right
    G goes from 0.0 to 1.0 from top to bottom

    */ 
    for (int j = 0; j < img_height; j++) {
        //process indicator to track rendering progress:
        std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' <<std::flush;
        for (int i = 0; i < img_width; i++) {
            auto pixel_color = color(double(i)/(img_width-1), double(j)/(img_height-1), 0);
            write_color(std::cout, pixel_color);

            /* If you cannot use the header files:
            auto r = double(i) / (img_width - 1);
            auto g = double(j) / (img_height - 1);
            auto b = 0.0;

            //color conversion to 8-bit
            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            //print the pixel RGB values to std out
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
            */
            
        }
    }
    std::clog << "\rDone. \n";
}