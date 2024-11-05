#include "GameObject.h"

using namespace crepe;
using namespace std;

GameObject::GameObject(uint32_t id, string name, string tag, int layer)
	: id(id), name(name), tag(tag), active(true), layer(layer) {}
