target_sources(crepe PUBLIC
	Asset.cpp
	Sound.cpp
	SoundContext.cpp
	SdlContext.cpp
	ComponentManager.cpp
	Component.cpp
	GameObject.cpp
	Collider.cpp
	Rigidbody.cpp
	ScriptSystem.cpp
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
	GameObject.h
	GameObject.hpp
	Collider.h
	Rigidbody.h
	System.h
	ScriptSystem.h
	RenderSystem.h
)

add_subdirectory(api)
add_subdirectory(util)

