
target_sources(crepe PUBLIC
	Asset.cpp
	Sound.cpp
	SoundContext.cpp
	Particle.cpp
	ParticleEmitter.cpp
	ParticleSystem.cpp
	SdlContext.cpp
	ComponentManager.cpp
	Component.cpp
	ScriptSystem.cpp
	RenderSystem.cpp
	PhysicsSystem.cpp
	Transform.cpp
	Force.cpp
	CollisionSystem.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Asset.h
	Sound.h
	SoundContext.h
	ParticleEmitter.h
	ParticleSystem.h
	Particle.h
	SdlContext.h
	ComponentManager.h
	ComponentManager.hpp
	Component.h
	System.h
	ScriptSystem.h
	PhysicsSystem.h
	Transform.h
	Force.h
	CollisionSystem.h
	RenderSystem.h
)

add_subdirectory(api)
add_subdirectory(util)

