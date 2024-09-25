cmake_minimum_required(VERSION 3.5)
project(ecs-entt)

# Set the C++ standard (optional, but good practice)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the EnTT submodule to the project
add_subdirectory(${CMAKE_SOURCE_DIR}/../../lib/entt ${CMAKE_BINARY_DIR}/entt)

add_executable(ecs-entt
	src/main.cpp
)

# Link the EnTT library to your project
target_link_libraries(ecs-entt PRIVATE EnTT::EnTT)

# Include EnTT header files and project headers
target_include_directories(ecs-entt PRIVATE ${CMAKE_SOURCE_DIR}/../../lib/entt/src)
target_include_directories(ecs-entt PRIVATE ${CMAKE_SOURCE_DIR}/include)
