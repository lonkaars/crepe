cmake_minimum_required(VERSION 3.28)
set(CMAKE_C_STANDARD 11)
project(whereami C)

include(CMakePackageConfigHelpers)

add_library(whereami SHARED)

target_include_directories(whereami PRIVATE SYSTEM lib/src)
target_sources(whereami PRIVATE lib/src/whereami.c)

install(
	TARGETS whereami
	EXPORT whereamiTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION lib
	INCLUDES DESTINATION include
)
install(
	FILES lib/src/whereami.h
	DESTINATION include
)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/whereami-config-version.cmake"
	VERSION 0.0.0
	COMPATIBILITY AnyNewerVersion
)
install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/whereami-config-version.cmake"
	DESTINATION lib/cmake/whereami
)
install(
	EXPORT whereamiTargets
	FILE whereami-config.cmake
	DESTINATION lib/cmake/whereami
)
