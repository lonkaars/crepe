#pragma once
#include "Component.hpp"

class PhysicsBody : public Component {
public:
    float mass;
    float velocityX, velocityY;
    float accelerationY;
    bool jetpackActive;

    PhysicsBody(float m, float vX, float vY);

    void Update() override;

    void ApplyPhysics(float& posX, float& posY, float deltaTime, int screenWidth, int screenHeight);

    void ActivateJetpack();
    void DeactivateJetpack();
};
