#include "PhysicsBody.hpp"
#include "iostream"
PhysicsBody::PhysicsBody(float m, float vX, float vY)
    : mass(m), velocityX(vX), velocityY(vY), accelerationY(2.5f), jetpackActive(false) {}

void PhysicsBody::Update() {
     std::cout << "active velocityY: "<< velocityY << std::endl;
    if (jetpackActive) {
           
        if (velocityY < -750) {          
            velocityY = -750;
        } else {
            velocityY -= 2.5f; 
        }
    } else {
        if (velocityY > 1000) {
            std::cout << "-10" << std::endl;
          
            velocityY = 1000;
        } else {
            velocityY += accelerationY;  
        }
        
    }
}

void PhysicsBody::ApplyPhysics(float& posX, float& posY, float deltaTime, int screenWidth, int screenHeight) {
 
    posX += velocityX * deltaTime;
    posY += velocityY * deltaTime;

   
    if (posX < 0) {
        posX = 0;
    } else if (posX + 50 > screenWidth) { 
        posX = screenWidth - 50;
    }

    if (posY < 0) {
        posY = 0;
    } else if (posY + 50 > screenHeight) { 
        posY = screenHeight - 50;
        velocityY = 0; 
    }
}

void PhysicsBody::ActivateJetpack() {
    jetpackActive = true;
}

void PhysicsBody::DeactivateJetpack() {
    jetpackActive = false;
}
