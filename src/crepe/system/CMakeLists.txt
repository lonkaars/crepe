target_sources(crepe PUBLIC
	System.cpp
	ParticleSystem.cpp
	ScriptSystem.cpp
	PhysicsSystem.cpp
	CollisionSystem.cpp
	RenderSystem.cpp
	AudioSystem.cpp
	AnimatorSystem.cpp
	InputSystem.cpp
	EventSystem.cpp
	ReplaySystem.cpp
	AISystem.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	System.h
	ScriptSystem.h
	PhysicsSystem.h
	CollisionSystem.h
	RenderSystem.h
	AudioSystem.h
	AnimatorSystem.h
	InputSystem.h
	EventSystem.h
	AISystem.h
)
