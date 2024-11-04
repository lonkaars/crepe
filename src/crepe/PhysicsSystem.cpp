#include <iostream>

#include "api/Force.h"
#include "api/Rigidbody.h"
#include "api/Transform.h"

#include "ComponentManager.h"
#include "PhysicsSystem.h"

#include <cmath>

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
		if(!rigidbody.active){continue;}
		switch (rigidbody.body_type) {
			case Rigidbody::BodyType::DYNAMIC:
				for (Transform & transform : transforms) {
					if (transform.game_object_id == rigidbody.game_object_id) {
						
						// Add gravity 
						if(rigidbody.use_gravity)
						{
							rigidbody.linear_velocity.y += (rigidbody.mass * rigidbody.gravity_scale * this->gravity);
						}
						// Add damping
						if(rigidbody.angular_damping != 0)
						{
							rigidbody.angular_velocity *= rigidbody.angular_damping;
						}
						if(rigidbody.linear_damping != Vector2{0,0})
						{
							rigidbody.linear_velocity *= rigidbody.linear_damping;
						}

						// Max velocity check
						if(rigidbody.angular_velocity > rigidbody.max_angular_velocity)
						{
							rigidbody.angular_velocity = rigidbody.max_angular_velocity;
						}
						else if (rigidbody.angular_velocity < -rigidbody.max_angular_velocity)
						{
							rigidbody.angular_velocity = -rigidbody.max_angular_velocity;
						}
						if(rigidbody.linear_velocity > rigidbody.max_linear_velocity)
						{
							rigidbody.linear_velocity = rigidbody.max_linear_velocity;
						}
						else if (rigidbody.linear_velocity > -rigidbody.max_linear_velocity)
						{
							rigidbody.linear_velocity = -rigidbody.max_linear_velocity;
						}
						// Move object 
						if(!rigidbody.constraints.rotation)
						{
							transform.rotation += rigidbody.angular_velocity;
							transform.rotation = std::fmod(transform.rotation, 360.0);
							if (transform.rotation < 0) {
								transform.rotation += 360.0;
							}
						}
						if(!rigidbody.constraints.x)
						{
							transform.position.x += rigidbody.linear_velocity.x;
						}
						if(!rigidbody.constraints.y)
						{
							transform.position.y += rigidbody.linear_velocity.y;
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
