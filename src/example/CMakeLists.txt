set(GAME_HEADERS
	Aquarium.h
	Background.h
	Forest.h
	Hallway.h
	Start.h
	GameScene.h
	Player.h
)

set(GAME_SOURCES
	game.cpp
	Aquarium.cpp
	Background.cpp
	Forest.cpp
	Hallway.cpp
	Start.cpp
	GameScene.cpp
	Player.cpp
)

add_executable(game ${GAME_SOURCES} ${GAME_HEADERS})

target_link_libraries(game PUBLIC crepe)
