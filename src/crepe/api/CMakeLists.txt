target_sources(crepe PUBLIC
	#Image_asset.cpp
	#map_asset.cpp
	#spritesheet.cpp
	#resource_manager.cpp
	Resource.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Resource.h
	#Image_asset.h
	#map_asset.h
	#spritesheet.h
	#resource_manager.h
	Component.h
	AudioSource.h
)
