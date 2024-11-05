target_sources(crepe PUBLIC
	LogColor.cpp
	log.cpp
	fmt.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	LogColor.h
	log.h
	fmt.h
	Proxy.h
	Proxy.hpp
)

