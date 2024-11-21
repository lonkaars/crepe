#include "Rigidbody.h"

using namespace crepe;

crepe::Rigidbody::Rigidbody(game_object_id_t id, const Data & data)
	: Component(id),
	  data(data) {}

void crepe::Rigidbody::add_force_linear(const Vector2<double> & force) {
	this->data.linear_velocity += force;
}

void crepe::Rigidbody::add_force_angular(double force) {
	this->data.angular_velocity += force;
}
