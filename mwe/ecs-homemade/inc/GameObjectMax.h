#pragma once

#include <cstdint>
#include <string>

class GameObject {
public:
	GameObject(std::uint32_t id, std::string name, std::string tag, int layer);

	template <typename T>
	void AddComponent(T* component);

	std::uint32_t mId;
	std::string mName;
	std::string mTag;
	bool mActive;
	int mLayer;
};

#include "GameObjectMax.hpp"
