target_sources(crepe PUBLIC
	Sound.cpp
	SoundSystem.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Sound.h
	SoundSystem.h
)

add_subdirectory(api)

