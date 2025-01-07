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
	player/PlayerScript.cpp
	player/PlayerSubScene.cpp
	StartGameScript.cpp
	player/PlayerEndScript.cpp
	player/PlayerAudioScript.cpp
	background/StartSubScene.cpp
	workers/WorkersSubScene.cpp
	workers/WorkerScript.cpp
	workers/PanicFromPlayerScript.cpp
	main.cpp
)

target_link_libraries(main PUBLIC crepe)

