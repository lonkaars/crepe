cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# # enable debug features
# set(CMAKE_BUILD_TYPE Debug)
# add_compile_definitions(DEBUG)

project(main C CXX)

add_executable(main
	main.cpp
)

