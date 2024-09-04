cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

project(main C CXX)

# Since we have the source code for the test library, we might as well let
# CMake use it so it automatically picks up the interface headers and compiles
# the library for us. The same can be achieved manually, but is more code.
add_subdirectory(../lib test)

add_executable(main main.c)

# Make sure ld.so (linux) looks in the same folder as the final executable for
# the .so dependency
set_target_properties(main PROPERTIES BUILD_RPATH "$ORIGIN")

# This links test (dynamically, as defined in ../lib/CMakeLists.txt) and makes
# the <lib.h> interface header available (also as defined in
# ../lib/CMakeLists.txt)
target_link_libraries(main PRIVATE test)

