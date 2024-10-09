add_executable(audio_internal EXCLUDE_FROM_ALL audio_internal.cpp)
target_link_libraries(audio_internal PUBLIC crepe)

add_executable(particel EXCLUDE_FROM_ALL particel.cpp)
target_link_libraries(particel PUBLIC crepe)

