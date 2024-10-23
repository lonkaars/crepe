target_sources(crepe PUBLIC
	# AudioSource.cpp
	BehaviorScript.cpp
	Script.cpp
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
)

