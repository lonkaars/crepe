target_sources(crepe PUBLIC
	color.cpp
	log.cpp
	fmt.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	color.h
	log.h
	fmt.h
)

