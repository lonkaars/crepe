#pragma once

#include "Components.h"
#include "ContiguousContainer.h"

class ComponentManager {
public:
	static ComponentManager& GetInstance();	//Singleton

	ComponentManager(const ComponentManager&) = delete;	//Singleton
    ComponentManager(ComponentManager&&) = delete;	//Singleton
    ComponentManager& operator=(const ComponentManager&) = delete;	//Singleton
    ComponentManager& operator=(ComponentManager&&) = delete;	//Singleton

	template<typename... Args>
    void addSpriteComponent(Args&&... args);
	template<typename... Args>
    void addRigidbodyComponent(Args&&... args);
	template<typename... Args>
    void addColiderComponent(Args&&... args);

	std::vector<std::reference_wrapper<Sprite>> getAllSpriteReferences();
	std::vector<std::reference_wrapper<Rigidbody>> getAllRigidbodyReferences();
	std::vector<std::reference_wrapper<Colider>> getAllColiderReferences();

private:
    static ComponentManager mInstance;	//Singleton

    ComponentManager();	//Singleton

	ContiguousContainer<Sprite> mSpriteContainer;
	ContiguousContainer<Rigidbody> mRigidbodyContainer;
	ContiguousContainer<Colider> mColiderContainer;
};

#include "ComponentManager.hpp"
