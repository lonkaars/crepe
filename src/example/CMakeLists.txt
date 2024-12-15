set(GAME_HEADERS
	menu/Menu.h
)

set(GAME_SOURCES
	game.cpp
	menu/Menu.cpp
)

add_executable(JetpackJoyride ${GAME_SOURCES} ${GAME_HEADERS})

target_link_libraries(JetpackJoyride PUBLIC crepe)
