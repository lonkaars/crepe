# all examples
add_custom_target(examples)

# add_example(target_name [SOURCES...])
function(add_example target_name)
	# if SOURCES is not specified
	if(NOT ARGV1)
		# A .cpp file with target_name exists, and should be used
		set(sources ${target_name}.cpp)
	else()
		set(sources ${ARGV})
	endif()

	add_executable(${target_name} EXCLUDE_FROM_ALL ${sources})
	target_link_libraries(${target_name} PUBLIC crepe)
	add_dependencies(examples ${target_name})
endfunction()

add_example(audio_internal)
add_example(components_internal)
add_example(script)
add_example(particle)
add_example(Physics)
target_link_libraries(particle PUBLIC SDL2)
target_link_libraries(Physics PUBLIC SDL2)
