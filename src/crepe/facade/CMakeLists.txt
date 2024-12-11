target_sources(crepe PUBLIC
	Sound.cpp
	Texture.cpp
	SoundContext.cpp
	SDLContext.cpp
	DB.cpp
	SDLFontContext.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Sound.h
	Texture.h
	SoundContext.h
	SDLContext.h
	DB.h
	SDLFontContext.h
)

