
target_sources(crepe PUBLIC
	Asset.cpp
	Sound.cpp
	SoundContext.cpp
	Particle.cpp
	ParticleEmitter.cpp
	ParticleSystem.cpp
	SDLApp.cpp
	ComponentManager.cpp
	Component.cpp
	GameObject.cpp
	Collider.cpp
	Rigidbody.cpp
	Sprite.cpp
	ScriptSystem.cpp
	Script.cpp
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
	SDLApp.h
	ComponentManager.h
	ComponentManager.hpp
	Component.h
	GameObject.h
	GameObject.hpp
	Collider.h
	Rigidbody.h
	Sprite.h
	System.h
	ScriptSystem.h
	PhysicsSystem.h
	Transform.h
	Force.h
	CollisionSystem.h
)

add_subdirectory(api)
add_subdirectory(util)

