#include "Rigidbody.h"

using namespace crepe;

crepe::Rigidbody::Rigidbody(const Component::Data & component_data, const Data & data)
	: Component(component_data),
	  data(data) {}

void crepe::Rigidbody::add_force_linear(const Vector2 & force) {
	this->data.linear_velocity += force;
}

void crepe::Rigidbody::add_force_angular(double force) {
	this->data.angular_velocity += force;
}
