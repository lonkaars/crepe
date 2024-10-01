#!/bin/bash

# creates the build dir and runs CMake with Ninja 
cmake -B build -G Ninja

# build the project
cmake --build build