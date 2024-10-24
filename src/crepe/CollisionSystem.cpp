#include "CollisionSystem.h"
#include "ComponentManager.h"
#include "api/BoxCollider.h"
#include "api/CircleCollider.h"
#include "api/Transform.h"
#include "api/Rigidbody.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace crepe::api;
using namespace crepe;

CollisionSystem::CollisionSystem() {}

bool CollisionSystem::checkAABBCollision(const BoxCollider& box1, const Transform& trf1,const crepe::api::Rigidbody& rgb1, const BoxCollider& box2, const Transform& trf2,const crepe::api::Rigidbody& rgb2) {
    return (box1.width + box2.width > std::abs((trf1.position.x+rgb1.velocity_x) - (trf2.position.x+rgb2.velocity_x)) &&
           box1.height + box2.height > std::abs((trf1.position.y+rgb1.velocity_y) - (trf2.position.y+rgb2.velocity_y)));
}

void CollisionSystem::detectBoxCollisions() {
    ComponentManager& mgr = ComponentManager::get_instance();
    std::vector<std::reference_wrapper<BoxCollider>> boxcolliders = mgr.get_components_by_type<BoxCollider>();
    
    // Detect Box-Box collisions
    for (std::vector<std::reference_wrapper<BoxCollider>>::iterator itOuter = boxcolliders.begin(); itOuter != boxcolliders.end(); ++itOuter) {
        for (std::vector<std::reference_wrapper<BoxCollider>>::iterator itInner = boxcolliders.begin(); itInner != boxcolliders.end(); ++itInner) {
			if (itOuter->get().game_object_id == itInner->get().game_object_id) {continue;}
            // Get location of the objects
            std::vector<std::reference_wrapper<Transform>> transformsOuter = 
                mgr.get_components_by_id<Transform>(itOuter->get().game_object_id);
            std::vector<std::reference_wrapper<Transform>> transformsInner = 
                mgr.get_components_by_id<Transform>(itInner->get().game_object_id);
			// Get velocities
			std::vector<std::reference_wrapper<Rigidbody>> rigidbodiesOuter = 
                mgr.get_components_by_id<Rigidbody>(itOuter->get().game_object_id);
            std::vector<std::reference_wrapper<Rigidbody>> rigidbodiesInner = 
                mgr.get_components_by_id<Rigidbody>(itInner->get().game_object_id);

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
				std::cout << "Collision detected between BoxCollider " 
							<< std::distance(boxcolliders.begin(), itOuter) << " and BoxCollider "
							<< std::distance(boxcolliders.begin(), itInner) << std::endl;
			}
            
        }
    }
}

void CollisionSystem::update() {
    this->detectBoxCollisions();

}
