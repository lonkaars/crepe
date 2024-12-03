#include <cmath>

#include "../ComponentManager.h"
#include "../api/Config.h"
#include "../api/Rigidbody.h"
#include "../api/Transform.h"
#include "../api/Vector2.h"

#include "PhysicsSystem.h"

using namespace crepe;

void PhysicsSystem::update() {
	ComponentManager & mgr = this->component_manager;
	RefVector<Rigidbody> rigidbodies = mgr.get_components_by_type<Rigidbody>();
	RefVector<Transform> transforms = mgr.get_components_by_type<Transform>();

	double gravity = Config::get_instance().physics.gravity;
	for (Rigidbody & rigidbody : rigidbodies) {
		if (!rigidbody.active) continue;

		switch (rigidbody.data.body_type) {
			case Rigidbody::BodyType::DYNAMIC:
				for (Transform & transform : transforms) {
					if (transform.game_object_id == rigidbody.game_object_id) {

						// Add gravity
						if (rigidbody.data.gravity_scale > 0) {
							rigidbody.data.linear_velocity.y
								+= (rigidbody.data.mass * rigidbody.data.gravity_scale
									* gravity);
						}
						// Add damping
						if (rigidbody.data.angular_velocity_coefficient > 0) {
							rigidbody.data.angular_velocity *= rigidbody.data.angular_velocity_coefficient;
						}
						if (rigidbody.data.linear_velocity_coefficient.x > 0 && rigidbody.data.linear_velocity_coefficient.y > 0) {
							rigidbody.data.linear_velocity *= rigidbody.data.linear_velocity_coefficient;
						}

						// Max velocity check
						if (rigidbody.data.angular_velocity
							> rigidbody.data.max_angular_velocity) {
							rigidbody.data.angular_velocity
								= rigidbody.data.max_angular_velocity;
						} else if (rigidbody.data.angular_velocity
								   < -rigidbody.data.max_angular_velocity) {
							rigidbody.data.angular_velocity
								= -rigidbody.data.max_angular_velocity;
						}

						if (rigidbody.data.linear_velocity.x
							> rigidbody.data.max_linear_velocity.x) {
							rigidbody.data.linear_velocity.x
								= rigidbody.data.max_linear_velocity.x;
						} else if (rigidbody.data.linear_velocity.x
								   < -rigidbody.data.max_linear_velocity.x) {
							rigidbody.data.linear_velocity.x
								= -rigidbody.data.max_linear_velocity.x;
						}

						if (rigidbody.data.linear_velocity.y
							> rigidbody.data.max_linear_velocity.y) {
							rigidbody.data.linear_velocity.y
								= rigidbody.data.max_linear_velocity.y;
						} else if (rigidbody.data.linear_velocity.y
								   < -rigidbody.data.max_linear_velocity.y) {
							rigidbody.data.linear_velocity.y
								= -rigidbody.data.max_linear_velocity.y;
						}

						// Move object
						if (!rigidbody.data.constraints.rotation) {
							transform.rotation += rigidbody.data.angular_velocity;
							transform.rotation = std::fmod(transform.rotation, 360.0);
							if (transform.rotation < 0) {
								transform.rotation += 360.0;
							}
						}
						if (!rigidbody.data.constraints.x) {
							transform.position.x += rigidbody.data.linear_velocity.x;
						}
						if (!rigidbody.data.constraints.y) {
							transform.position.y += rigidbody.data.linear_velocity.y;
						}
					}
				}
				break;
			case Rigidbody::BodyType::KINEMATIC:
				break; //(scripts)
			case Rigidbody::BodyType::STATIC:
				break; //(unmoveable objects)
			default:
				break;
		}
	}
}
