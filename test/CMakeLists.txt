cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_BUILD_TYPE Debug)

project(test C CXX)

add_subdirectory(../lib/googletest googletest)
add_subdirectory(../src crepe)

add_executable(test
	dummy.cpp
	# audio.cpp
)

target_link_libraries(test
	PRIVATE gtest_main
	PUBLIC crepe # TODO: this does not work properly
)

