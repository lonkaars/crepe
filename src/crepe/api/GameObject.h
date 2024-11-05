#pragma once

#include <cstdint>
#include <string>

#include "api/Point.h"

namespace crepe::api {

class GameObject {
public:
	GameObject(uint32_t id, std::string name, std::string tag, Point position, double rotation, double scale);
	void set_parent(GameObject & parent);

	template <typename T, typename... Args>
	T & add_component(Args &&... args);

	uint32_t id;
};

} // namespace crepe::api

#include "GameObject.hpp"
