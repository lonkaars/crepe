target_sources(main PUBLIC
	Gameobject.cpp
    main.cpp
	PhysicsSystem.cpp
	Transform.cpp
    ViewFacade.cpp
)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
