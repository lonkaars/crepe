#include "ViewFacade.hpp"
#include "Square.hpp"
#include "PhysicsBody.hpp"
#include "Collider.hpp"
#include <iostream>

int main() {
    ViewFacade view;
    if (!view.initialize("Physics Squares", 800, 600)) {
        std::cerr << "Failed to initialize the view facade!" << std::endl;
        return -1;
    }

    Square square1(100, 100, 50, 50);
    Square square2(100, 460, 50, 5);

    PhysicsBody* physics1 = new PhysicsBody(1.0f, 0.0f, 0.0f);
    PhysicsBody* physics2 = new PhysicsBody(1.0f, 0.0f, 0.0f);
    Collider* collider1 = new Collider();
    Collider* collider2 = new Collider();

    square1.AddComponent(physics1);
    square1.AddComponent(collider1);
    square2.AddComponent(physics2);
    square2.AddComponent(collider2);

    // Game loop
    while (view.isRunning()) {
        view.handleEvents();

        view.updateDeltaTime();
        float deltaTime = view.getDeltaTime();

        square1.UpdateComponents();
        square2.UpdateComponents();

        physics1->ApplyPhysics(square1.x, square1.y, deltaTime, 800, 600);
        physics2->ApplyPhysics(square2.x, square2.y, deltaTime, 800, 600);

       
        if (view.isSpacePressed()) {
            physics1->ActivateJetpack(); 
        } else {
            physics1->DeactivateJetpack();
        }

        if (collider1->CheckCollision(square1.x, square1.y, square1.width, square1.height,
                                      square2.x, square2.y, square2.width, square2.height)) {
            std::cout << "The squares are touching!" << std::endl;
            return 0;
        }

        view.clear();

        view.drawSquare(static_cast<int>(square1.x), static_cast<int>(square1.y), square1.width, square1.height, 255, 0, 0);
        view.drawSquare(static_cast<int>(square2.x), static_cast<int>(square2.y), square2.width, square2.height, 0, 255, 0);

        view.present();
    }

    return 0;
}
