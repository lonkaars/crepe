cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# enable debug features
set(CMAKE_BUILD_TYPE Debug)
add_compile_definitions(DEBUG)

add_subdirectory(../lib/soloud soloud)

project(crepe C CXX)

add_library(crepe SHARED)

target_include_directories(crepe
	PUBLIC SYSTEM INTERFACE .
)

# TODO: libraries should be linked as PRIVATE
target_link_libraries(crepe
	PUBLIC soloud
)

add_subdirectory(crepe)

install(
	TARGETS crepe
	FILE_SET HEADERS DESTINATION include/crepe
)


add_executable(dummy_audio dummy_audio.cpp)
target_link_libraries(dummy_audio PUBLIC crepe)

