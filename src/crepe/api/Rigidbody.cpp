#include "Rigidbody.h"

using namespace crepe;

crepe::Rigidbody::Rigidbody(uint32_t game_object_id, const Data & data)
	: Component(game_object_id), data(data) {}

void crepe::Rigidbody::add_force_linear(const Vector2 & force) {
	this->data.linear_velocity += force;
}

void crepe::Rigidbody::add_force_angular(double force) {
	this->data.angular_velocity += force;
}
