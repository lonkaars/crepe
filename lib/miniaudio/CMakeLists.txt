cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

project(miniaudio C CXX)

add_library(miniaudio STATIC main.c)
target_include_directories(miniaudio SYSTEM INTERFACE lib)

