#pragma once

#include <string>

namespace crepe {

class Component {
public:
	Component();

	bool m_active;
};

// TODO: these should be in separate files

class Sprite : public Component {
public:
	Sprite(std::string path);

	std::string m_path;
};

class Rigidbody : public Component {
public:
	Rigidbody(int mass, int gravityScale, int bodyType);

	int m_mass;
	int m_gravity_scale;
	int m_body_type;
};

class Collider : public Component {
public:
	Collider(int size);

	int m_size;
};

} // namespace crepe
