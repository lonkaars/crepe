cmake_minimum_required(VERSION 3.5)
project(ecs-homemake)

# Set the C++ standard (optional, but good practice)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ecs-homemake
	src/main.cpp
	src/ComponentManager.cpp
	src/Components.cpp
	src/GameObjectMax.cpp
)
target_include_directories(ecs-homemake PRIVATE "${CMAKE_SOURCE_DIR}/inc")
