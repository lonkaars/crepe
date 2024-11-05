#pragma once

#include <cstdint>
#include <string>

namespace crepe {

class GameObject {
public:
	GameObject(uint32_t id, std::string name, std::string tag, const Vector2 & position, double rotation, double scale);
	void set_parent(const GameObject & parent);

	template <typename T, typename... Args>
	T & add_component(Args &&... args);

	uint32_t id;
};

} // namespace crepe

#include "GameObject.hpp"
