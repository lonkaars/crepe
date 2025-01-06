cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)

project(game C CXX)

add_subdirectory(../src crepe)
add_executable(main
	#subscenes
	background/AquariumSubScene.cpp
	background/BackgroundSubScene.cpp
	background/ForestSubScene.cpp
	background/HallwaySubScene.cpp
	background/StartSubScene.cpp
	PlayerSubScene.cpp

	# preview subscenes
	preview/PrevPlayerSubScene.cpp
	preview/PrevPlayerScript.cpp
	
	#scripts
	MoveCameraManualyScript.cpp
	background/ForestParallaxScript.cpp
	PlayerScript.cpp
	StartGameScript.cpp

	#scenes
	GameScene.cpp
	PreviewScene.cpp
	main.cpp
)

target_link_libraries(main PUBLIC crepe)

