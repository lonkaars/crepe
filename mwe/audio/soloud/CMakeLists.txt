cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(../../../lib/soloud soloud)

project(poc C CXX)

add_executable(main
	main.cpp
)

target_link_libraries(main
	soloud
)

