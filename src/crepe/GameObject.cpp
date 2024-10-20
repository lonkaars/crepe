#include "GameObject.h"
#include "Transform.h"

using namespace crepe;

GameObject::GameObject(uint32_t id, std::string name, std::string tag,
					   int layer)
	: id(id), name(name), tag(tag), active(true), layer(layer) 
{
	Position pos = {0,0};
	this->add_component<Transform>(pos, 0, 0);
}
