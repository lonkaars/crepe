target_sources(crepe PUBLIC
	LogColor.cpp
	Log.cpp
	Private.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	LogColor.h
	Log.h
	Log.hpp
	Proxy.h
	Proxy.hpp
	OptionalRef.h
	OptionalRef.hpp
	Private.h
	Private.hpp
)

