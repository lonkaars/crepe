#include "Components.h"
#include <iostream>

using namespace crepe;

Component::Component() : mActive(true) {}

Sprite::Sprite(std::string path) : mPath(path) {}

Rigidbody::Rigidbody(int mass, int gravityScale, int bodyType)
	: mMass(mass), mGravityScale(gravityScale), mBodyType(bodyType) {}

Colider::Colider(int size) : mSize(size) {}
