#include <cmath>

#include "../api/Config.h"
#include "../api/Rigidbody.h"
#include "../api/Transform.h"
#include "../api/Vector2.h"
#include "../manager/ComponentManager.h"
#include "../manager/LoopTimerManager.h"
#include "../manager/Mediator.h"

#include "PhysicsSystem.h"

using namespace crepe;

void PhysicsSystem::update() {

	const Mediator & mediator = this->mediator;
	ComponentManager & mgr = mediator.component_manager;
	LoopTimerManager & loop_timer = mediator.loop_timer;
	RefVector<Rigidbody> rigidbodies = mgr.get_components_by_type<Rigidbody>();
	float dt = loop_timer.get_scaled_fixed_delta_time();

	float gravity = Config::get_instance().physics.gravity;
	for (Rigidbody & rigidbody : rigidbodies) {
		if (!rigidbody.active) continue;
		Transform & transform
			= mgr.get_components_by_id<Transform>(rigidbody.game_object_id).front().get();

		switch (rigidbody.data.body_type) {
			case Rigidbody::BodyType::DYNAMIC:
				if (transform.game_object_id == rigidbody.game_object_id) {
					// Add gravity

					if (rigidbody.data.mass <= 0) {
						throw std::runtime_error("Mass must be greater than 0");
					}

					if (gravity <= 0) {
						throw std::runtime_error("Config Gravity must be greater than 0");
					}

					if (rigidbody.data.gravity_scale > 0 && !rigidbody.data.constraints.y) {
						rigidbody.data.linear_velocity.y
							+= (rigidbody.data.mass * rigidbody.data.gravity_scale * gravity
								* dt);
					}
					// Add coefficient rotation
					if (rigidbody.data.angular_velocity_coefficient > 0) {
						rigidbody.data.angular_velocity
							*= std::pow(rigidbody.data.angular_velocity_coefficient, dt);
					}

					// Add coefficient movement horizontal
					if (rigidbody.data.linear_velocity_coefficient.x > 0
						&& !rigidbody.data.constraints.x) {
						rigidbody.data.linear_velocity.x
							*= std::pow(rigidbody.data.linear_velocity_coefficient.x, dt);
					}

					// Add coefficient movement horizontal
					if (rigidbody.data.linear_velocity_coefficient.y > 0
						&& !rigidbody.data.constraints.y) {
						rigidbody.data.linear_velocity.y
							*= std::pow(rigidbody.data.linear_velocity_coefficient.y, dt);
					}

					// Max velocity check
					if (rigidbody.data.angular_velocity
						> rigidbody.data.max_angular_velocity) {
						rigidbody.data.angular_velocity = rigidbody.data.max_angular_velocity;
					} else if (rigidbody.data.angular_velocity
							   < -rigidbody.data.max_angular_velocity) {
						rigidbody.data.angular_velocity = -rigidbody.data.max_angular_velocity;
					}

					// Set max velocity to maximum length
					if (rigidbody.data.linear_velocity.length()
						> rigidbody.data.max_linear_velocity) {
						rigidbody.data.linear_velocity.normalize();
						rigidbody.data.linear_velocity *= rigidbody.data.max_linear_velocity;
					}

					// Move object
					if (!rigidbody.data.constraints.rotation) {
						transform.rotation += rigidbody.data.angular_velocity * dt;
						transform.rotation = std::fmod(transform.rotation, 360.0);
						if (transform.rotation < 0) {
							transform.rotation += 360.0;
						}
					}
					if (!rigidbody.data.constraints.x) {
						transform.position.x += rigidbody.data.linear_velocity.x * dt;
					}
					if (!rigidbody.data.constraints.y) {
						transform.position.y += rigidbody.data.linear_velocity.y * dt;
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
