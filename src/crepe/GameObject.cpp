#include "GameObject.h"

#include "ComponentManager.h"

using namespace crepe;

GameObject::GameObject(std::uint32_t id, std::string name, std::string tag,
					   int layer)
	: mId(id), mName(name), mTag(tag), mActive(true), mLayer(layer) {}
