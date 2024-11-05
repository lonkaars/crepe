target_sources(crepe PUBLIC
	Asset.cpp
	Sound.cpp
	SoundContext.cpp
	Particle.cpp
	ParticleSystem.cpp
	SDLApp.cpp
	ComponentManager.cpp
	Component.cpp
	ScriptSystem.cpp
	PhysicsSystem.cpp
	CollisionSystem.cpp
	Collider.cpp
	SDLContext.cpp
	RenderSystem.cpp
	Metadata.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Asset.h
	Sound.h
	SoundContext.h
	SDLContext.h
	ComponentManager.h
	ComponentManager.hpp
	Component.h
	System.h
	ScriptSystem.h
	PhysicsSystem.h
	CollisionSystem.h
	Collider.h
	SDLContext.h
	RenderSystem.h
	Metadata.h
)

add_subdirectory(api)
add_subdirectory(util)

