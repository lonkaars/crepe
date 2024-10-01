#include "PhysicsSystem.hpp"
#include "Component.hpp"

void PhysicsSystem::ApplyForces(std::vector<GameObject*> gameObjects, float deltaTime) {
    for (GameObject* obj : gameObjects) {
        RigidBody* rb = nullptr;
        for (Component *cmp : obj->components)
        {
            rb = dynamic_cast<RigidBody*>(cmp);
            if (rb) {
                break; // Exit the loop if we found a RigidBody
            }
        }        
        if (rb) 
        {
            ApplyGravity(rb, deltaTime);
            obj->transform.SetPosition(obj->transform.position[0]+rb->velocity[0],obj->transform.position[1]+rb->velocity[1]);
        }
    }
}

void PhysicsSystem::ApplyGravity(RigidBody* rb, float deltaTime)
{
    rb->velocity[1] += rb->mass * rb->gravityScale * 9.8f * deltaTime;
}
