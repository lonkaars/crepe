set(GAME_HEADERS
	AquariumSubScene.h
	BackgroundSubScene.h
	ForestSubScene.h
	ForestParallaxScript.h
	HallwaySubScene.h
	StartSubScene.h
	GameScene.h
	StartGameScript.h
	MoveCameraManualyScript.h
	PlayerSubScene.h
	PlayerScript.h
)

set(GAME_SOURCES
	game.cpp
	AquariumSubScene.cpp
	BackgroundSubScene.cpp
	ForestSubScene.cpp
	ForestParallaxScript.cpp
	HallwaySubScene.cpp
	StartSubScene.cpp
	GameScene.cpp
	StartGameScript.cpp
	MoveCameraManualyScript.cpp
	PlayerSubScene.cpp
	PlayerScript.cpp
)

add_executable(game ${GAME_SOURCES} ${GAME_HEADERS})

target_link_libraries(game PUBLIC crepe)
