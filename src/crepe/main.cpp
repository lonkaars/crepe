#include "Gameobject.hpp"
#include "RigidBody.hpp"
#include "PhysicsSystem.hpp"
#include <iostream>

int main() {
    // Create the PhysicsSystem
    PhysicsSystem physicsSystem;

    // Create a GameObject
    GameObject* player = new GameObject("Player", "PlayerTag", 0);

    // Create a RigidBody component for the player
    RigidBody* playerRigidBody = new RigidBody(10.0f, 1.0f, BodyType::Dynamic);

    // Add the RigidBody component to the player GameObject
    player->AddComponent(playerRigidBody);

    // Create a vector of GameObjects (you could add more objects here)
    std::vector<GameObject*> gameObjects;
    gameObjects.push_back(player);

    // Simulate a frame in the game loop with deltaTime (e.g., 0.016 for ~60 FPS)
    float deltaTime = 0.016f;

    // Apply forces to all gameObjects (only applies to objects with a RigidBody)
    physicsSystem.ApplyForces(gameObjects, deltaTime);

    // Output the new velocity after applying gravity
    std::cout << "Player's y-velocity after gravity: " << playerRigidBody->velocity[1] << std::endl;

    // Clean up
    delete playerRigidBody;
    delete player;

    return 0;
}
