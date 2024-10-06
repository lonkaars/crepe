#include "Components.h"

using namespace crepe;
using namespace std;

Component::Component() : active(true) {}

Sprite::Sprite(string path) : path(path) {}

Rigidbody::Rigidbody(int mass, int gravityScale, int bodyType)
	: mass(mass), gravity_scale(gravityScale), body_type(bodyType) {}

Collider::Collider(int size) : size(size) {}
