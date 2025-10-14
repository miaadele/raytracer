#!/bin/zsh

#compile make file
g++ -std=c++11 -o gradient main.cc

#check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
    ./gradient > gradient.ppm
else
    echo "Compilation failed."
fi