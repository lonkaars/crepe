set(GAME_HEADERS
	menu/MenuScene.h
	menu/MainMenuButton.h
	menu/MainMenuScript.h
)

set(GAME_SOURCES
	game.cpp
	menu/MenuScene.cpp
	menu/MainMenuButton.cpp
	menu/MainMenuScript.cpp
)

add_executable(JetpackJoyride ${GAME_SOURCES} ${GAME_HEADERS})

target_link_libraries(JetpackJoyride PUBLIC crepe)
