cmake_minimum_required(VERSION 3.5)
project(gameloop)

# Set the C++ standard (optional, but good practice)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)

# Find the SDL2 package
find_package(SDL2 REQUIRED)
# Find the SDL2_ttf package
find_package(SDL2_ttf REQUIRED)

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
    src/inputSystem.cpp
    src/uiRenderer.cpp
    src/uiObject.cpp
)

target_link_libraries(gameloop ${SDL2_LIBRARIES} SDL2_ttf::SDL2_ttf)

# Include SDL2 header files and project headers
target_include_directories(gameloop PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(gameloop PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Copy font files to the build directory
file(COPY ${PROJECT_SOURCE_DIR}/font DESTINATION ${CMAKE_BINARY_DIR})
