cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)
project(segvcatch CXX)

include(CMakePackageConfigHelpers)

add_library(segvcatch SHARED lib/lib/segvcatch.cpp)

install(
	TARGETS segvcatch
	EXPORT segvcatchTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION lib
	INCLUDES DESTINATION include
)
install(
	FILES lib/lib/segvcatch.h
	DESTINATION include
)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/segvcatch-config-version.cmake"
	VERSION 0.0.0
	COMPATIBILITY AnyNewerVersion
)
install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/segvcatch-config-version.cmake"
	DESTINATION lib/cmake/segvcatch
)
install(
	EXPORT segvcatchTargets
	FILE segvcatch-config.cmake
	DESTINATION lib/cmake/segvcatch
)
