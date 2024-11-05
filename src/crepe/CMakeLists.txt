target_sources(crepe PUBLIC
	Asset.cpp
	Sound.cpp
	SoundContext.cpp
	Particle.cpp
	SDLApp.cpp
	ComponentManager.cpp
	Component.cpp
	Collider.cpp
	SDLContext.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Asset.h
	Sound.h
	SoundContext.h
	SDLContext.h
	ComponentManager.h
	ComponentManager.hpp
	Component.h
	Collider.h
	SDLContext.h
)

add_subdirectory(api)
add_subdirectory(util)
add_subdirectory(system)

