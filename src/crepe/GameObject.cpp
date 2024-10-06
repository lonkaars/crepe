#include "GameObject.h"

using namespace crepe;

GameObject::GameObject(std::uint32_t id, std::string name, std::string tag,
					   int layer)
	: id(id), name(name), tag(tag), active(true), layer(layer) {}
