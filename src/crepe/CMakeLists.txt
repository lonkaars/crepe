target_sources(crepe PUBLIC
	Particle.cpp
	ComponentManager.cpp
	Component.cpp
	Collider.cpp
	Resource.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	ComponentManager.h
	ComponentManager.hpp
	Component.h
	Collider.h
	ValueBroker.h
	ValueBroker.hpp
	Resource.h
)

add_subdirectory(api)
add_subdirectory(facade)
add_subdirectory(system)
add_subdirectory(util)

