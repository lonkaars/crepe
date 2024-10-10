
target_sources(crepe PUBLIC
	Asset.cpp
	Sound.cpp
	SoundContext.cpp
	main.cpp
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
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Asset.h
	Sound.h
	SoundContext.h
	ParticleEmitter.hpp
	ParticleSystem.hpp
	Particle.hpp
	SDLApp.hpp
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
)

add_subdirectory(api)
add_subdirectory(util)

