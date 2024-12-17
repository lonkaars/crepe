set(GAME_HEADERS
	Aquarium.h
	Background.h
	Forest.h
	Hallway.h
	Start.h
)

set(GAME_SOURCES
	game.cpp
	Aquarium.cpp
	Background.cpp
	Forest.cpp
	Hallway.cpp
	Start.cpp
)

add_executable(game ${GAME_SOURCES} ${GAME_HEADERS})

target_link_libraries(game PUBLIC crepe)
