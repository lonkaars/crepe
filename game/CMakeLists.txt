cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)

project(game C CXX)

add_subdirectory(../src crepe)

set(SOURCES
	AquariumSubScene.cpp
	BackgroundSubScene.cpp
	ForestParallaxScript.cpp
	ForestSubScene.cpp
	GameScene.cpp
	HallwaySubScene.cpp
	MoveCameraManualyScript.cpp
	PlayerScript.cpp
	PlayerSubScene.cpp
	StartGameScript.cpp
	StartSubScene.cpp
	main.cpp
	mainmenu/IButtonScript.cpp
	mainmenu/ButtonSubScene.cpp
	mainmenu/MainMenuScene.cpp
	mainmenu/IShowScript.cpp
	mainmenu/ShowStartScript.cpp
	mainmenu/ShowPreviewScript.cpp
	mainmenu/ShopMenuScene.cpp
	mainmenu/BannerSubScene.cpp
	mainmenu/SetShopScript.cpp
)

set(HEADERS
	AquariumSubScene.h
	BackgroundSubScene.h
	ForestParallaxScript.h
	ForestSubScene.h
	GameScene.h
	HallwaySubScene.h
	MoveCameraManualyScript.h
	PlayerScript.h
	PlayerSubScene.h
	StartGameScript.h
	StartSubScene.h
	mainmenu/IButtonScript.h
	mainmenu/ButtonSubScene.h
	mainmenu/MainMenuScene.h
	mainmenu/MainMenuConfig.h
	mainmenu/IShowScript.h
	mainmenu/ShowStartScript.h
	mainmenu/ShowPreviewScript.h
	mainmenu/ShopMenuScene.h
	mainmenu/BannerSubScene.h
	mainmenu/SetShopScript.h
)

add_executable(main ${SOURCES} ${HEADERS})

target_link_libraries(main PUBLIC crepe)

