#pragma once
#include <cstdint>
#include <string>
class GameObject {
public:
	GameObject() {}

	// template <typename... Args>
	// void addSpriteComponent(Args &&... args);
	// template <typename... Args>
	// void addRigidbodyComponent(Args &&... args);
	// template <typename... Args>
	// void addColiderComponent(Args &&... args);

	std::uint32_t mId;
	std::string mName;
	std::string mTag;
	bool mActive;
	int mLayer;
};
