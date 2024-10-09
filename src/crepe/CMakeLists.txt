
target_sources(crepe PUBLIC
	Asset.cpp
	Sound.cpp
	SoundContext.cpp
	main.cpp
	Particle.cpp
	ParticleEmitter.cpp
	ParticleSystem.cpp
	SDLApp.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Asset.h
	Sound.h
	SoundContext.h
	ParticleEmitter.hpp
	ParticleSystem.hpp
	Particle.hpp
	SDLApp.hpp
)

add_subdirectory(api)
add_subdirectory(util)

