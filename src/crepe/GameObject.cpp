#include "GameObject.h"

#include "ComponentManager.h"

using namespace crepe;

GameObject::GameObject(std::uint32_t id, std::string name, std::string tag,
					   int layer)
	: m_id(id), m_name(name), m_tag(tag), m_active(true), m_layer(layer) {}
