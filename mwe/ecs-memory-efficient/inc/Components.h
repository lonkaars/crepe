#pragma once

#include <string>

class Component {
public:
	Component();

	bool mActive;
};

class Sprite : public Component {
public:
	Sprite(std::string path);

	std::string mPath;
};

class Rigidbody : public Component {
public:
	Rigidbody(int mass, int gravityScale, int bodyType);

	int mMass;
	int mGravityScale;
	int mBodyType;
};

class Colider : public Component {
public:
	Colider(int size);

	int mSize;
};
