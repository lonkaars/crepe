target_sources(crepe PUBLIC
	# AudioSource.cpp
	BehaviorScript.cpp
	Script.cpp
	GameObject.cpp
	Rigidbody.cpp
	ParticleEmitter.cpp
	Transform.cpp
	Color.cpp
	Texture.cpp
	AssetManager.cpp
	Sprite.cpp
	SaveManager.cpp
	Config.cpp
	Metadata.cpp
	Scene.cpp
	SceneManager.cpp
	Vector2.cpp
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
	Vector2.h
	Color.h
	Texture.h 
	AssetManager.h 
	AssetManager.hpp
	SaveManager.h
	Scene.h
	Metadata.h
	SceneManager.h
	SceneManager.hpp
)
