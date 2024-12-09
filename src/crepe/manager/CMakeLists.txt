target_sources(crepe PUBLIC
	ComponentManager.cpp
	EventManager.cpp
	Manager.cpp
	SaveManager.cpp
	SceneManager.cpp
	LoopTimerManager.cpp
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
	LoopTimerManager.h
)

