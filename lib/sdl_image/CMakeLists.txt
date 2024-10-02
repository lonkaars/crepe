cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

#add_compile_definitions(WITH_SDL2)
#add_subdirectory(../sdl2 sdl2)

include_directories(src/include/SDL3_image)

project(sdl_image C CXX)

add_library(sdl_image SHARED
    src/src/IMG.c
    src/src/IMG_WIC.c
    src/src/IMG_avif.c
    src/src/IMG_bmp.c
    src/src/IMG_gif.c
    src/src/IMG_jpg.c
     src/src/IMG_jxl.c
	src/src/IMG_lbm.c
    src/src/IMG_pcx.c
    src/src/IMG_png.c
    src/src/IMG_pnm.c
    src/src/IMG_qoi.c
    src/src/IMG_stb.c
	src/src/IMG_svg.c
    src/src/IMG_tga.c
    src/src/IMG_tif.c
    src/src/IMG_webp.c
    src/src/IMG_xcf.c
    src/src/IMG_xpm.c
    src/src/IMG_xv.c












)
target_include_directories(sdl_image PRIVATE src/include/)
target_include_directories(sdl_image SYSTEM INTERFACE src/include/)

target_link_libraries(sdl_image PRIVATE SDL2)

