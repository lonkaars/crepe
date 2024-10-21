target_sources(crepe PUBLIC
	# AudioSource.cpp
	BehaviorScript.cpp
	Script.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	# AudioSource.h
	BehaviorScript.h
	Config.h
	Script.h
)

