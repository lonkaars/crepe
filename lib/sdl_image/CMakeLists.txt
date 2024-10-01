cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

#add_compile_definitions(WITH_SDL2)
#add_subdirectory(../sdl2 sdl2)

include_directories(src/include/SDL3_image)

project(sdl_image C CXX)

add_library(sdl_image SHARED
	src/src/IMG.c
	src/src/IMG_png.c
)
target_include_directories(sdl_image PRIVATE src/include/)
target_include_directories(sdl_image SYSTEM INTERFACE src/include/)

target_link_libraries(sdl_image PRIVATE SDL2)

