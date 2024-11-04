#include "Rigidbody.h"

using namespace crepe::api;
Rigidbody::Rigidbody(
	uint32_t game_object_id, double mass, double gravity_scale,
	BodyType body_type, const Vector2& linear_velocity, 
	const Vector2& max_linear_velocity,	const Vector2& linear_damping, 
	double angular_velocity,	double max_angular_velocity, 
	double angular_damping, physics_constraints constraints, bool use_gravity,	bool bounce) :
	Component(game_object_id), mass(mass), gravity_scale(gravity_scale),body_type(body_type), linear_velocity(linear_velocity), 
	max_linear_velocity(max_linear_velocity), linear_damping(linear_damping), angular_velocity(angular_velocity),
	max_angular_velocity(max_angular_velocity), 
	angular_damping(angular_damping), constraints(constraints), use_gravity(use_gravity), bounce(bounce) {}
