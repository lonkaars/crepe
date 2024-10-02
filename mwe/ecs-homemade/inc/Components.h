#pragma once

class Component {
public:
	Component();

	bool mActive;
};

class Sprite : public Component {
public:
	void Render();
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
