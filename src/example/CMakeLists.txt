set(GAME_HEADERS
	AquariumSubScene.h
	BackgroundSubScene.h
	ForestSubScene.h
	HallwaySubScene.h
	StartSubScene.h
	GameScene.h
	PlayerSubScene.h
)

set(GAME_SOURCES
	game.cpp
	AquariumSubScene.cpp
	BackgroundSubScene.cpp
	ForestSubScene.cpp
	HallwaySubScene.cpp
	StartSubScene.cpp
	GameScene.cpp
	PlayerSubScene.cpp
)

add_executable(game ${GAME_SOURCES} ${GAME_HEADERS})

target_link_libraries(game PUBLIC crepe)
