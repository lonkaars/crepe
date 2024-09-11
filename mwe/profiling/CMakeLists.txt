cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

project(main C CXX)

add_subdirectory(lib)

add_executable(main main.c)

target_link_libraries(main PRIVATE test)

