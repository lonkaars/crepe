#include "GameObjectMax.h"

#include "ComponentManager.h"

GameObject::GameObject(std::uint32_t id, std::string name, std::string tag, int layer)
	: mId(id),
	  mName(name),
	  mTag(tag),
	  mActive(true),
	  mLayer(layer) {}
