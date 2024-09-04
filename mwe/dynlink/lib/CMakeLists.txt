cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

project(lib C CXX)

add_library(test SHARED lib.c)
target_include_directories(test SYSTEM INTERFACE .)

