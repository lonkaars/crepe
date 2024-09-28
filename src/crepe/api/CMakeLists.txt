target_sources(crepe PUBLIC
	# AudioSource.cpp
	Resource.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	AudioSource.h
	Component.h
	Resource.h
)

