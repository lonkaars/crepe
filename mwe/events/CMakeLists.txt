cmake_minimum_required(VERSION 3.5)
project(gameloop)

# Set the C++ standard (optional, but good practice)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)

# Find the SDL2 package
find_package(SDL2 REQUIRED)

add_executable(gameloop
	src/window.cpp
	src/main.cpp
	src/eventManager.cpp
	src/event.cpp
	src/loopManager.cpp
	src/timer.cpp
	src/keyCodes.cpp
	src/eventHandler.cpp
	src/iMouseListener.cpp
	src/iKeyListener.cpp
	src/mouseListenerTest.cpp
	src/keyListenerTest.cpp
)
add_subdirectory(../../lib/SDL_ttf SDL_ttf)
# Link the SDL2 library to your project
target_link_libraries(gameloop ${SDL2_LIBRARIES})

# Include SDL2 header files and project headers
target_include_directories(gameloop PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(gameloop PRIVATE ${CMAKE_SOURCE_DIR}/include)

file(COPY ${PROJECT_SOURCE_DIR}/font DESTINATION ${CMAKE_BINARY_DIR})
