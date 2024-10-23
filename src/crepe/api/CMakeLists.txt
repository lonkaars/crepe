target_sources(crepe PUBLIC
	# AudioSource.cpp
	BehaviorScript.cpp
	Script.cpp
	Color.cpp
	Texture.cpp
	Sprite.cpp
	Transform.cpp
	AssetManager.cpp
	GameObject.cpp
	Collider.cpp
	Rigidbody.cpp
	Sprite.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	# AudioSource.h
	BehaviorScript.h
	Script.h
	GameObject.h
	GameObject.hpp
	Collider.h
	Rigidbody.h
	Sprite.h
	Point.h
	Transform.h 
	Color.h 
	Sprite.h
	Texture.h 
	AssetManager.h 
)
