#!/bin/bash

# creates the build dir and runs CMake with Ninja 
cmake -B build -G Ninja

ninja -C build

ninja -C build/ rendering
