target_sources(main PUBLIC
    main.cpp
	Particle.cpp
	ParticleEmitter.cpp
	ParticleSystem.cpp
	SDLApp.cpp
)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
