target_sources(crepe PUBLIC
	Sound.cpp
	SoundContext.cpp
	SDLApp.cpp
	SDLContext.cpp
	DB.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Sound.h
	SoundContext.h
	SDLContext.h
	SDLContext.h
	DB.h
)

