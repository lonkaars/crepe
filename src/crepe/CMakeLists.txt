target_sources(crepe PUBLIC
	Asset.cpp
	Sound.cpp
	SoundContext.cpp
	ComponentManager.cpp
	Components.cpp
	GameObject.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Asset.h
	Sound.h
	SoundContext.h
	ComponentManager.h
	ComponentManager.hpp
	Components.h
	GameObject.h
	GameObject.hpp
)

add_subdirectory(api)
add_subdirectory(util)

