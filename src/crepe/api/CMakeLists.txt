target_sources(crepe PUBLIC
	# AudioSource.cpp
	BehaviorScript.cpp
	Script.cpp
	GameObject.cpp
	Rigidbody.cpp
	Force.cpp
	ParticleEmitter.cpp
	Transform.cpp
	Color.cpp
	Texture.cpp
	AssetManager.cpp
	Sprite.cpp

	timer.cpp
	loopManager.cpp
	eventManager.cpp
	eventHandler.cpp
	event.cpp

	Camera.cpp
	Animator.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	# AudioSource.h
	BehaviorScript.h
	Config.h
	Script.h
	Script.hpp
	GameObject.h
	GameObject.hpp
	Rigidbody.h
	Sprite.h
	Point.h
	Color.h
	Texture.h 
	AssetManager.h 
	AssetManager.hpp
	
	timer.h 
	loopManager.h 
	eventManager.h 
	eventHandler.h 
	event.h

	Camera.h
	Animator.h

)
