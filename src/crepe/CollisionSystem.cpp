#include "CollisionSystem.h"
#include "ComponentManager.h"
#include "api/BoxCollider.h"
#include "api/CircleCollider.h"
#include "api/Transform.h"
#include "api/Rigidbody.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "api/event.h"
#include "api/eventManager.h"
#include "api/Point.h"

using namespace crepe;
using namespace crepe::api;


CollisionSystem::CollisionSystem() {
	
}

bool CollisionSystem::checkAABBCollision(
    const BoxCollider& box1, const Transform& trf1, const crepe::api::Rigidbody& rgb1,
    const BoxCollider& box2, const Transform& trf2, const crepe::api::Rigidbody& rgb2) {
    
    float halfWidth1 = box1.width / 2.0f;
    float halfHeight1 = box1.height / 2.0f;
    float halfWidth2 = box2.width / 2.0f;
    float halfHeight2 = box2.height / 2.0f;

    float centerX1 = trf1.position.x + rgb1.velocity.y;
    float centerY1 = trf1.position.y + rgb1.velocity.y;
    float centerX2 = trf2.position.x + rgb2.velocity.x;
    float centerY2 = trf2.position.y + rgb2.velocity.y;

    return (std::abs(centerX1 - centerX2) < (halfWidth1 + halfWidth2) &&
            std::abs(centerY1 - centerY2) < (halfHeight1 + halfHeight2));
}


void CollisionSystem::detectBoxCollisions(std::vector<std::pair<int, int>>& collisions) {
    ComponentManager& mgr = ComponentManager::get_instance();
    std::vector<std::reference_wrapper<BoxCollider>> boxcolliders = mgr.get_components_by_type<BoxCollider>();
    
    // Detect Box-Box collisions
    for (std::vector<std::reference_wrapper<BoxCollider>>::iterator itOuter = boxcolliders.begin(); itOuter != boxcolliders.end(); ++itOuter) {
        for (std::vector<std::reference_wrapper<BoxCollider>>::iterator itInner = boxcolliders.begin(); itInner != boxcolliders.end(); ++itInner) {
			int gameobject_outer = itOuter->get().game_object_id;
			int gameobject_inner = itInner->get().game_object_id;
			if (gameobject_outer == gameobject_inner) {continue;}
            // Get location of the objects
			
            std::vector<std::reference_wrapper<Transform>> transformsOuter = 
                mgr.get_components_by_id<Transform>(gameobject_outer);
            std::vector<std::reference_wrapper<Transform>> transformsInner = 
                mgr.get_components_by_id<Transform>(gameobject_inner);
			// Get velocities
			std::vector<std::reference_wrapper<Rigidbody>> rigidbodiesOuter = 
                mgr.get_components_by_id<Rigidbody>(gameobject_outer);
            std::vector<std::reference_wrapper<Rigidbody>> rigidbodiesInner = 
                mgr.get_components_by_id<Rigidbody>(gameobject_inner);

            // Check if transform and rigidbody is available
            if (transformsOuter.empty() || transformsInner.empty()) {continue;}
			if (rigidbodiesOuter.empty() || rigidbodiesInner.empty()) {continue;}

			// Always take first rigid body and transform
			const Transform& transformOuter = transformsOuter.front().get();
			const Transform& transformInner = transformsInner.front().get();
			const Rigidbody& rigidbodyOuter = rigidbodiesOuter.front().get();
			const Rigidbody& rigidbodyInner = rigidbodiesInner.front().get();

			// Pass references to the checkAABBCollision function
			if (this->checkAABBCollision(itOuter->get(), transformOuter, rigidbodyOuter, itInner->get(), transformInner,rigidbodyInner)) {
				// Handle box-box collision
				collisions.emplace_back(gameobject_outer, gameobject_inner);
			}
        }
    }
}

void CollisionSystem::handleCollision(std::vector<std::pair<int, int>>& collisions) {
    ComponentManager& mgr = ComponentManager::get_instance();
    std::vector<std::reference_wrapper<Rigidbody>> rigidbodies = mgr.get_components_by_type<Rigidbody>();

    for (Rigidbody& rigidbody : rigidbodies) {
        // Move the object according to its velocity
        std::vector<std::reference_wrapper<Transform>> transforms = mgr.get_components_by_id<Transform>(rigidbody.game_object_id);
        Transform& transform = transforms.front().get();
        transform.position.x += rigidbody.velocity.x;
        transform.position.y += rigidbody.velocity.y;

        // Check collisions after moving
        for (const auto& collision : collisions) {
            if (rigidbody.game_object_id != collision.first) { continue; }

            std::vector<std::reference_wrapper<Rigidbody>> collidedBody = mgr.get_components_by_id<Rigidbody>(collision.second);
            std::vector<std::reference_wrapper<Transform>> collidedTransforms = mgr.get_components_by_id<Transform>(collision.second);
            Transform& collidedTransform = collidedTransforms.front().get();

            // Retrieve BoxCollider components for the current and collided objects
            std::vector<std::reference_wrapper<BoxCollider>> boxColliders = mgr.get_components_by_id<BoxCollider>(rigidbody.game_object_id);
            std::vector<std::reference_wrapper<BoxCollider>> collidedBoxColliders = mgr.get_components_by_id<BoxCollider>(collision.second);

            if (boxColliders.empty() || collidedBoxColliders.empty()) { continue; }

            const BoxCollider& boxCollider = boxColliders.front().get();
            const BoxCollider& collidedBoxCollider = collidedBoxColliders.front().get();

            float halfWidth1 = boxCollider.width / 2.0f;
            float halfHeight1 = boxCollider.height / 2.0f;
            float halfWidth2 = collidedBoxCollider.width / 2.0f;
            float halfHeight2 = collidedBoxCollider.height / 2.0f;

            float deltaX = transform.position.x - collidedTransform.position.x;
            float deltaY = transform.position.y - collidedTransform.position.y;
            float overlapX = (halfWidth1 + halfWidth2) - std::abs(deltaX);
            float overlapY = (halfHeight1 + halfHeight2) - std::abs(deltaY);

            if (collidedBody.front().get().body_type == BodyType::STATIC) {
                // Resolve collision based on the smallest overlap
                if (overlapX < overlapY) {
                    transform.position.x += (deltaX > 0 ? overlapX : -overlapX);
                    rigidbody.velocity.x = 0;  // Stop movement in X
                } else {
                    transform.position.y += (deltaY > 0 ? overlapY : -overlapY);
                    rigidbody.velocity.y = 0;  // Stop movement in Y
                }
            } else {
                // Handle dynamic collisions here
            }
            break;
        }
    }
}

void CollisionSystem::update() {
	std::cout << "Update Collision " << std::endl;
	std::vector<std::pair<int, int>> collisions;
	
    // Call detectBoxCollisions and pass the vector to store collisions
    this->detectBoxCollisions(collisions);

    // Process the collisions here (for example, resolve them)
    for (const auto& collision : collisions) {
        std::cout << "( collision tussen object " << collision.first << " en object " << collision.second << ") " << std::endl;
    }
	this->handleCollision(collisions);
	
}
