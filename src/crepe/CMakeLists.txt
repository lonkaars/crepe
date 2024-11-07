target_sources(crepe PUBLIC
	Asset.cpp
	Particle.cpp
	ComponentManager.cpp
	Component.cpp
	Collider.cpp
	Metadata.cpp

	keyCodes.cpp
	AnimatorSystem.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Asset.h
	ComponentManager.h
	ComponentManager.hpp
	Component.h
	Collider.h
	Metadata.h

	keyCodes.h

	AnimatorSystem.h
)

add_subdirectory(api)
add_subdirectory(facade)
add_subdirectory(system)
add_subdirectory(util)

