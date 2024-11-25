target_sources(crepe PUBLIC
	System.cpp
	ParticleSystem.cpp
	ScriptSystem.cpp
	PhysicsSystem.cpp
	CollisionSystem.cpp
	RenderSystem.cpp
	AnimatorSystem.cpp
	InputSystem.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	System.h
	ScriptSystem.h
	PhysicsSystem.h
	CollisionSystem.h
	RenderSystem.h
	AnimatorSystem.h
	InputSystem.h
)
