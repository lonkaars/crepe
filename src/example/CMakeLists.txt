set(GAME_HEADERS
)

set(GAME_SOURCES
	game.cpp
)

add_executable(JetpackJoyride ${GAME_SOURCES} ${GAME_HEADERS})

target_link_libraries(JetpackJoyride PUBLIC crepe)
