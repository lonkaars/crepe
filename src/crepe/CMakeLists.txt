target_sources(crepe PUBLIC
	Asset.cpp
	Sound.cpp
	SoundContext.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Asset.h
	Sound.h
	SoundContext.h
)

add_subdirectory(api)
add_subdirectory(util)

