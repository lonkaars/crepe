#pragma once

#include "Components.h"
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <any>

class ComponentManager {
public:
	static ComponentManager& GetInstance();

	ComponentManager(const ComponentManager&) = delete;
    ComponentManager(ComponentManager&&) = delete;
    ComponentManager& operator=(const ComponentManager&) = delete;
    ComponentManager& operator=(ComponentManager&&) = delete;

	template <typename T, typename... Args>
	void AddComponent(std::uint32_t id, Args&&... args);
	template <typename T>
    std::vector<std::reference_wrapper<T>> GetComponentsOfID(std::uint32_t id);
	/*template <typename T>
	std::vector<std::uint32_t> GetAllComponentIDs();
	template <typename T>
	std::vector<T*> GetAllComponentPointer();*/

private:
    static ComponentManager mInstance;

    ComponentManager();

	std::unordered_map<std::type_index, std::vector<std::vector<std::unique_ptr<Component>>>> mComponents;
};

#include "ComponentManager.hpp"
