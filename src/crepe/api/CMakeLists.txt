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
	Scene.cpp
	SceneManager.cpp
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
	Color.h
	Texture.h 
	AssetManager.h 
	AssetManager.hpp
	BoxCollider.h
	CircleCollider.h
	timer.h 
	loopManager.h 
	eventManager.h 
	eventHandler.h 
	event.h
	Camera.h
	Scene.h
	SceneManager.h
	SceneManager.hpp
)
