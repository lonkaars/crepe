target_sources(crepe PUBLIC
	# AudioSource.cpp
	BehaviorScript.cpp
	Script.cpp
	GameObject.cpp
	Rigidbody.cpp
	Sprite.cpp
	Force.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	# AudioSource.h
	BehaviorScript.h
	Script.h
	GameObject.h
	GameObject.hpp
	Rigidbody.h
	Sprite.h
	Force.h
)

