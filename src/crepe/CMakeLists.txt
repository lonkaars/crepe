target_sources(crepe PUBLIC
	Asset.cpp
	Sound.cpp
	SoundContext.cpp
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
add_subdirectory(fabricator)
add_subdirectory(facade)
add_subdirectory(core)

