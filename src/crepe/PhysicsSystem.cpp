#include "PhysicsSystem.h"
#include "ComponentManager.h"
#include "Rigidbody.h"
#include "Transform.h"
#include <iostream>

using namespace crepe;

PhysicsSystem::PhysicsSystem() {

}

void PhysicsSystem::update() {
	ComponentManager& mgr = ComponentManager::get_instance();
	std::vector<std::reference_wrapper<Rigidbody>> rigidbodies = mgr.get_components_by_type<Rigidbody>();
	std::vector<std::reference_wrapper<Transform>> transforms = mgr.get_components_by_type<Transform>();
	for (Rigidbody& rigidbody : rigidbodies) {
		std::cout << rigidbody.gameObjectId << std::endl;
	}
}
