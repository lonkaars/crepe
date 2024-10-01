target_sources(crepe PUBLIC
	Sound.cpp
	SoundContext.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Sound.h
	SoundContext.h
)

add_subdirectory(api)
add_subdirectory(util)

