target_sources(crepe PUBLIC
	ParticleSystem.cpp
	ScriptSystem.cpp
	PhysicsSystem.cpp
	CollisionSystem.cpp
	RenderSystem.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	System.h
	ScriptSystem.h
	PhysicsSystem.h
	CollisionSystem.h
	RenderSystem.h
)
