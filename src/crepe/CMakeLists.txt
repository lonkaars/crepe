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
	SdlContext.cpp

	RenderSystem.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Asset.h
	Sound.h
	SoundContext.h
	SdlContext.h
	ComponentManager.h
	ComponentManager.hpp
	Component.h
	System.h
	ScriptSystem.h
	PhysicsSystem.h
	CollisionSystem.h
	Collider.h
	SdlContext.h
	RenderSystem.h
)

add_subdirectory(api)
add_subdirectory(util)

