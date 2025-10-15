#!/bin/zsh

#compile create_gradient file
g++ -std=c++11 -o gradient create_gradient.cc

#check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
    ./gradient > gradient.ppm

    #convert PPM to PNG
    if command -v magick >/dev/null 2>&1; then
        magick gradient.ppm gradient.png
        echo "converted gradient.ppm to gradient.png"
    else
        echo "ImageMagick not found."
    fi
else
    echo "Compilation failed."
fi

#compile main file
g++ -std=c++11 -o linear_gradient main.cc

#check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
    ./linear_gradient > linear_gradient.ppm

    #convert PPM to PNG
    if command -v magick >/dev/null 2>&1; then
        magick linear_gradient.ppm linear_gradient.png
        echo "converted linear_gradient.ppm to linear_gradient.png"
    else
        echo "ImageMagick not found."
    fi
else
    echo "Compilation failed."
fi