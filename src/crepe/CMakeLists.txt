target_sources(main PUBLIC
    main.cpp
    ViewFacade.cpp
    Square.cpp
    PhysicsBody.cpp
    Collider.cpp
    GameObject.cpp
)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
