#include <cmath>

#include "../api/Config.h"
#include "../api/Rigidbody.h"
#include "../api/Transform.h"
#include "../api/Vector2.h"
#include "../manager/ComponentManager.h"

#include "PhysicsSystem.h"

using namespace crepe;

void PhysicsSystem::update() {
	double dt = LoopTimer::get_instance().get_delta_time();
	ComponentManager & mgr = this->mediator.component_manager;
	RefVector<Rigidbody> rigidbodies = mgr.get_components_by_type<Rigidbody>();
	RefVector<Transform> transforms = mgr.get_components_by_type<Transform>();

	float gravity = Config::get_instance().physics.gravity;
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
									* gravity * dt);
						}
						// Add coefficient rotation
						if (rigidbody.data.angular_velocity_coefficient > 0) {
							rigidbody.data.angular_velocity
								*= std::pow(rigidbody.data.angular_velocity_coefficient, dt);
								
						}

						// Add coefficient movement horizontal
						if (rigidbody.data.linear_velocity_coefficient.x > 0)
						{
							rigidbody.data.linear_velocity.x
									*= std::pow(rigidbody.data.linear_velocity_coefficient.x, dt);
						}

						// Add coefficient movement horizontal
						if (rigidbody.data.linear_velocity_coefficient.y > 0)
						{
							rigidbody.data.linear_velocity.y
									*= std::pow(rigidbody.data.linear_velocity_coefficient.y, dt);
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
						
						// Set max velocity to maximum length
						if(rigidbody.data.linear_velocity.length() > rigidbody.data.max_linear_velocity) {
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
