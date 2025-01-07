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

	# preview
	preview/PrevPlayerSubScene.cpp
	preview/PrevPlayerScript.cpp
	preview/NpcSubScene.cpp
	preview/NpcScript.cpp
	preview/SmokeSubScene.cpp
	preview/MissleScript.cpp

	# Missle
	missile/MissileSubScene.cpp
	missile/CollisionScript.cpp
	missile/MissilePool.cpp
	missile/SpawnEvent.cpp
	
	#scripts
	MoveCameraManualyScript.cpp
	player/PlayerScript.cpp
	player/PlayerSubScene.cpp
	background/ForestParallaxScript.cpp

	StartGameScript.cpp
	player/PlayerEndScript.cpp

	#scenes
	GameScene.cpp
	PreviewScene.cpp
	main.cpp
)

target_link_libraries(main PUBLIC crepe)

