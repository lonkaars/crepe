#include <iostream>

#include "../api/Force.h"
#include "../api/Rigidbody.h"
#include "../api/Transform.h"
#include "../ComponentManager.h"

#include "PhysicsSystem.h"

using namespace crepe;
using namespace crepe::api;

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update() {
	ComponentManager & mgr = ComponentManager::get_instance();
	std::vector<std::reference_wrapper<Rigidbody>> rigidbodies
		= mgr.get_components_by_type<Rigidbody>();
	std::vector<std::reference_wrapper<Transform>> transforms
		= mgr.get_components_by_type<Transform>();

	for (Rigidbody & rigidbody : rigidbodies) {

		switch (rigidbody.body_type) {
			case BodyType::DYNAMIC:
				for (Transform & transform : transforms) {
					if (transform.game_object_id == rigidbody.game_object_id) {
						rigidbody.velocity_x = 0;
						rigidbody.velocity_y = 0;
						std::vector<std::reference_wrapper<Force>> forces
							= mgr.get_components_by_id<Force>(
								rigidbody.game_object_id);
						rigidbody.velocity_y
							+= rigidbody.gravity_scale * 1 * rigidbody.mass;

						for (Force & force : forces) {
							rigidbody.velocity_x += force.force_x;
							rigidbody.velocity_y += force.force_y;
						}

						std::cout << "before transform.postion.x "
								  << transform.position.x << std::endl;
						std::cout << "before transform.postion.y "
								  << transform.position.y << std::endl;
						transform.position.x += rigidbody.velocity_x;
						transform.position.y += rigidbody.velocity_y;
						std::cout << "after transform.postion.x "
								  << transform.position.x << std::endl;
						std::cout << "after transform.postion.y "
								  << transform.position.y << std::endl;
					}
				}
				break;
			case BodyType::KINEMATIC:
				break; //(scripts)
			case BodyType::STATIC:
				break; //(unmoveable objects)
			default:
				break;
		}
	}
}
