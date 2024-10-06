#pragma once

#include <cstdint>
#include <string>

namespace crepe {

class GameObject {
public:
	GameObject(std::uint32_t id, std::string name, std::string tag, int layer);

	template <typename T, typename... Args>
	void add_component(Args &&... args);

	std::uint32_t m_id;
	std::string m_name;
	std::string m_tag;
	bool m_active;
	int m_layer;
};

} // namespace crepe
