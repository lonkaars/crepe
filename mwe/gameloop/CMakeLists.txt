cmake_minimum_required(VERSION 3.5)
project(gameloop)

# Set the C++ standard (optional, but good practice)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the SDL2 package
find_package(SDL2 REQUIRED)

add_executable(gameloop
	src/loopManager.cpp
	src/window.cpp
	src/main.cpp
	src/eventManager.cpp
	src/gameObject.cpp
	src/timer.cpp
)

# Link the SDL2 library to your project
target_link_libraries(gameloop ${SDL2_LIBRARIES})

# Include SDL2 header files and project headers
target_include_directories(gameloop PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(gameloop PRIVATE ${CMAKE_SOURCE_DIR}/include)

