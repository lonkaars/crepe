cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)

project(game C CXX)

add_subdirectory(../src crepe)
add_executable(main
	background/AquariumSubScene.cpp
	background/BackgroundSubScene.cpp
	background/ForestParallaxScript.cpp
	background/ForestSubScene.cpp
	GameScene.cpp
	background/HallwaySubScene.cpp
	MoveCameraManualyScript.cpp
	PlayerScript.cpp
	PlayerSubScene.cpp
	StartGameScript.cpp
	background/StartSubScene.cpp
	main.cpp
)

target_link_libraries(main PUBLIC crepe)

