
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
	Transform.cpp
	CollisionSystem.cpp
	Collider.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Asset.h
	Sound.h
	SoundContext.h
	ParticleSystem.h
	Particle.h
	SDLApp.h
	ComponentManager.h
	ComponentManager.hpp
	Component.h
	System.h
	ScriptSystem.h
	PhysicsSystem.h
	Transform.h
	CollisionSystem.h
	Collider.h
)

add_subdirectory(api)
add_subdirectory(util)

