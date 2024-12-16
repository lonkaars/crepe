target_sources(crepe PUBLIC
	LogColor.cpp
	Log.cpp
	AbsoluutPosition.cpp
)

target_sources(crepe PUBLIC FILE_SET HEADERS FILES
	LogColor.h
	Log.h
	Log.hpp
	Proxy.h
	Proxy.hpp
	OptionalRef.h
	OptionalRef.hpp
	AbsoluutPosition.h
)

