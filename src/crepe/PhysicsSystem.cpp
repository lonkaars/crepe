#include "PhysicsSystem.h"
#include "ComponentManager.h"
#include "api/Rigidbody.h"
#include "api/Transform.h"
#include "Force.h"
#include <iostream>

using namespace crepe;
using namespace crepe::api;

PhysicsSystem::PhysicsSystem() {

}

void PhysicsSystem::update() {
	ComponentManager& mgr = ComponentManager::get_instance();
	std::vector<std::reference_wrapper<Rigidbody>> rigidbodies = mgr.get_components_by_type<Rigidbody>();
	std::vector<std::reference_wrapper<Transform>> transforms = mgr.get_components_by_type<Transform>();
	
	for (Rigidbody& rigidbody : rigidbodies) {

		switch (rigidbody.body_type)
		{
		case BodyType::Dynamic :
			for (Transform& transform : transforms) {
				if(transform.gameObjectId == rigidbody.gameObjectId)
				{
					rigidbody.velocity_x = 0;
					rigidbody.velocity_y = 0;
					std::vector<std::reference_wrapper<Force>> Forces = mgr.get_components_by_id<Force>(rigidbody.gameObjectId);
					rigidbody.velocity_y += rigidbody.gravity_scale * 1 * rigidbody.mass;

					for (Force& force : Forces)
					{
						rigidbody.velocity_x += force.force_x;
						rigidbody.velocity_y += force.force_y;	
					}
					
					std::cout << "before transform.postion.x " << transform.postion.x << std::endl;
					std::cout << "before transform.postion.y " << transform.postion.y << std::endl;
					transform.postion.x += rigidbody.velocity_x;
					transform.postion.y += rigidbody.velocity_y;
					std::cout << "after transform.postion.x " << transform.postion.x << std::endl;
					std::cout << "after transform.postion.y " << transform.postion.y << std::endl;
				}
			}	
			break;
		case BodyType::Kinematic :
			break; //(scripts)
		case BodyType::Static :
			break; //(unmoveable objects)
		default:
			break;
		}
	}
}
