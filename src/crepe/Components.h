#pragma once

#include <string>

namespace crepe {

class Component {
public:
	Component();

	bool active;
};

// TODO: these should be in separate files

class Sprite : public Component {
public:
	Sprite(std::string path);

	std::string path;
};

class Rigidbody : public Component {
public:
	Rigidbody(int mass, int gravityScale, int bodyType);

	int mass;
	int gravity_scale;
	int body_type;
};

class Collider : public Component {
public:
	Collider(int size);

	int size;
};

} // namespace crepe
