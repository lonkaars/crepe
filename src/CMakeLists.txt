cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)

project(crepe C CXX)

find_package(SDL2 REQUIRED)
find_package(SoLoud REQUIRED)
find_package(GTest REQUIRED)

add_library(crepe SHARED)
add_executable(test_main EXCLUDE_FROM_ALL)

target_include_directories(crepe
	PUBLIC SYSTEM INTERFACE .
)

target_link_libraries(crepe
	PRIVATE soloud
	PRIVATE SDL2
)

add_subdirectory(crepe)
add_subdirectory(test)
add_subdirectory(example)

install(
	TARGETS crepe
	FILE_SET HEADERS DESTINATION include/crepe
)

target_link_libraries(test_main
	PRIVATE gtest_main
	PUBLIC crepe
)

