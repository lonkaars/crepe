cmake_minimum_required(VERSION 3.5)
project(ecs-memory-efficient)

# Set the C++ standard (optional, but good practice)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Use the debug mode (otherwise breakpoints are not compiled)
set(CMAKE_BUILD_TYPE Debug)

add_executable(ecs-memory-efficient
	src/main.cpp
	src/ComponentManager.cpp
	src/Components.cpp
	src/GameObjectMax.cpp
)
target_include_directories(ecs-memory-efficient PRIVATE "${CMAKE_SOURCE_DIR}/inc")
