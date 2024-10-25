#include <iostream>

#include "api/Force.h"
#include "api/Rigidbody.h"
#include "api/Transform.h"

#include "ComponentManager.h"
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
						rigidbody.velocity.x = 0;
						rigidbody.velocity.y = 0;
						std::vector<std::reference_wrapper<Force>> forces
							= mgr.get_components_by_id<Force>(
								rigidbody.game_object_id);
						rigidbody.velocity.y
							+= rigidbody.gravity_scale * 1 * rigidbody.mass;

						for (Force & force : forces) {
							rigidbody.velocity.x += force.force_x;
							rigidbody.velocity.y += force.force_y;
						}
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
