target_sources(crepe PUBLIC
	Image_asset.cpp
	map_asset.cpp
	Audio_asset.cpp
	spritesheet.cpp
	resource_manager.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	resource.h
	Image_asset.h
	map_asset.h
	Audio_asset.h
	spritesheet.h
	resource_manager.h
)

