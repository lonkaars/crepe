cmake_minimum_required(VERSION 3.28)

# Set C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Enable debug features
set(CMAKE_BUILD_TYPE Debug)
add_compile_definitions(DEBUG)

# Project name and supported languages
project(crepe C CXX)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Add all source files to the executable
add_executable(main 
    main.cpp
    Audio_asset.cpp
    Image_asset.cpp
    resource_fabricator.cpp
    resource_manager.cpp
	constants.cpp
)

# Include directories for headers
target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} .)

# Link SDL2 library
target_link_libraries(main PRIVATE ${SDL2_LIBRARIES} SDL2_image::SDL2_image)

