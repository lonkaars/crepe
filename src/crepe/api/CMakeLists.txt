target_sources(crepe PUBLIC
	#map_asset.cpp
	spritesheet.cpp
	resource_manager.cpp
	Resource.cpp
	game.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	Resource.h
	baseResource.h
	game.h
	#map_asset.h
	spritesheet.h
	resource_manager.h
	Component.h
	AudioSource.h
)
