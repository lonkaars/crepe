#pragma once

#include <cstdint>
#include <string>

namespace crepe {

class GameObject {
public:
	GameObject(uint32_t id, std::string name, std::string tag, int layer);

	template <typename T, typename... Args>
	void add_component(Args &&... args);

	uint32_t id;
	std::string name;
	std::string tag;
	bool active;
	int layer;
};

} // namespace crepe

#include "GameObject.hpp"
