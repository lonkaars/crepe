target_sources(crepe PUBLIC
	Sound.cpp
	SoundContext.cpp
	Texture.cpp
	SdlContext.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Sound.h
	SoundContext.h
	Texture.h
	SdlContext.h
)
