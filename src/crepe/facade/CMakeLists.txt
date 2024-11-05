target_sources(crepe PUBLIC
	Sound.cpp
	SoundContext.cpp
	SDLContext.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Sound.h
	SoundContext.h
	SDLContext.h
)

