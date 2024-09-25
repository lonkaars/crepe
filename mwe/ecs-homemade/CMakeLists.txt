cmake_minimum_required(VERSION 3.5)
project(ecs-homemake)

# Set the C++ standard (optional, but good practice)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ecs-homemake
	src/main.cpp
)
