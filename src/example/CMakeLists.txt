set(GAME_HEADERS
	menu/Menu.h
	menu/MainMenuButton.h
)

set(GAME_SOURCES
	game.cpp
	menu/Menu.cpp
	menu/MainMenuButton.cpp
)

add_executable(JetpackJoyride ${GAME_SOURCES} ${GAME_HEADERS})

target_link_libraries(JetpackJoyride PUBLIC crepe)
