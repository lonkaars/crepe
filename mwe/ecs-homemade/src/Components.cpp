#include "Components.h"
#include <iostream>

Component::Component() : mActive(true) {}

void Sprite::Render() {
	std::cout << "Rendering sprite" << std::endl;
}

Rigidbody::Rigidbody(int mass, int gravityScale, int bodyType) : mMass(mass), mGravityScale(gravityScale), mBodyType(bodyType) {}

Colider::Colider(int size) : mSize(size) {}
