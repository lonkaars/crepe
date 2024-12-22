cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)

project(game C CXX)

add_subdirectory(../src crepe)

add_executable(main)

target_sources(main PUBLIC
	GameScene.cpp
	MoveCameraManualyScript.cpp
	StartGameScript.cpp
	main.cpp
)

add_subdirectory(background)
add_subdirectory(prefab)

target_link_libraries(main PUBLIC crepe)
target_include_directories(main PRIVATE .)

