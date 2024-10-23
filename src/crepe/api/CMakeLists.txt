target_sources(crepe PUBLIC
	# AudioSource.cpp
	BehaviorScript.cpp
	Script.cpp
	Color.cpp
	Texture.cpp
	Sprite.cpp
	Transform.cpp
	AssetManager.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	# AudioSource.h
	BehaviorScript.h
	Script.h
	Point.h
	Transform.h 
	Color.h 
	Sprite.h
	Texture.h 
	AssetManager.h 
)
