target_sources(crepe PUBLIC
	ComponentManager.cpp
	EventManager.cpp
	Manager.cpp
	SaveManager.cpp
	SceneManager.cpp
	ResourceManager.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	ComponentManager.h
	ComponentManager.hpp
	EventManager.h
	EventManager.hpp
	Manager.h
	Mediator.h
	SaveManager.h
	SceneManager.h
	SceneManager.hpp
	ResourceManager.h
	ResourceManager.hpp
)

