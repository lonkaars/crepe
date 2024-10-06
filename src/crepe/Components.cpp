#include "Components.h"
#include <iostream>

using namespace crepe;

Component::Component() : m_active(true) {}

Sprite::Sprite(std::string path) : m_path(path) {}

Rigidbody::Rigidbody(int mass, int gravityScale, int bodyType)
	: m_mass(mass), m_gravity_scale(gravityScale), m_body_type(bodyType) {}

Collider::Collider(int size) : m_size(size) {}

