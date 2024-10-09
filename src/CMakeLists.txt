cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_BUILD_TYPE Debug)
add_compile_definitions(DEBUG)

add_subdirectory(../lib/soloud soloud)
add_subdirectory(../lib/googletest googletest)
add_subdirectory(../lib/sdl2 sdl2)

project(crepe C CXX)

add_library(crepe SHARED)
add_executable(test_main EXCLUDE_FROM_ALL)

target_include_directories(crepe
	PUBLIC SYSTEM INTERFACE .
)

# TODO: libraries should be linked as PRIVATE
target_link_libraries(crepe
	PUBLIC soloud
	PUBLIC sdl2	
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

add_subdirectory(crepe)
