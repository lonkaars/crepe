#include "GameObject.h"

using namespace crepe;

GameObject::GameObject(uint32_t id, std::string name, std::string tag,
					   int layer)
	: id(id), name(name), tag(tag), active(true), layer(layer) {}
