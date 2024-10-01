#pragma once
#include <vector>
#include "Gameobject.hpp"
#include "RigidBody.hpp"

class PhysicsSystem {
public: // forces
    void ApplyForces(std::vector<GameObject*> gameObjects, float deltaTime);
private:
    void ApplyGravity(RigidBody* rb, float deltaTime);
    void ApplyMovement(RigidBody*  rb, float deltaTime);
    void ApplyPlayerMovement(RigidBody*  rb, float deltaTime);
    void ApplyBounce(RigidBody*  obj);jaro
    
    void ApplyRotation(RigidBody*  rb, float deltaTime);
    void ApplyDirectionalForce(RigidBody*  rb, float forceX, float forceY);

public:// collisions
    void DetectCollsions();
private:
    bool DetectCollision(GameObject& obj1, GameObject& obj2);
    void HandleCollision(GameObject& obj1, GameObject& obj2);
};
