#pragma once

#include <cstdint>
#include <string>

class GameObject {
public:
	GameObject(std::uint32_t id, std::string name, std::string tag, int layer);

	template<typename... Args>
    void addSpriteComponent(Args&&... args);
	template<typename... Args>
    void addRigidbodyComponent(Args&&... args);
	template<typename... Args>
    void addColiderComponent(Args&&... args);

	std::uint32_t mId;
	std::string mName;
	std::string mTag;
	bool mActive;
	int mLayer;
};

#include "GameObjectMax.hpp"
