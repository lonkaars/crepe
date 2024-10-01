#pragma once
#include "Component.hpp"

enum class BodyType {
    Static,
    Dynamic,
    KinematicUser,
    KinematicEngine
};

class RigidBody : public Component {
public:
    float mass;
    float gravityScale;
    BodyType bodyType;
    float velocity[2]; // Store x and y velocity

    RigidBody(float mass, float gravityScale, BodyType bodyType)
        : mass(mass), gravityScale(gravityScale), bodyType(bodyType) {
        velocity[0] = 0.0f; // Initial x velocity
        velocity[1] = 0.0f; // Initial y velocity
    }
};
