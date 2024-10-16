#pragma once

#include <string>
#include <memory>

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

class IBehaviour {
public:
	virtual ~IBehaviour() = default;
	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
};

template<typename T>
class BehaviourWrapper : public IBehaviour {
public:
	BehaviourWrapper();
	void onStart() override;
	void onUpdate() override;

private:
	T instance;
};

class BehaviourScript : public Component {
public:
	template<typename T>
	void addScript();

	void onStart();
	void onUpdate();

private:
	std::unique_ptr<IBehaviour> behaviour;
};

#include "Components.hpp"
