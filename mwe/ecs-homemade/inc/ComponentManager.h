#pragma once

#include "Components.h"
#include <cstdint>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

class ComponentManager {
public:
	static ComponentManager & GetInstance(); //Singleton

	ComponentManager(const ComponentManager &) = delete; //Singleton
	ComponentManager(ComponentManager &&) = delete; //Singleton
	ComponentManager & operator=(const ComponentManager &) = delete; //Singleton
	ComponentManager & operator=(ComponentManager &&) = delete; //Singleton

	template <typename T, typename... Args>
	T& AddComponent(std::uint32_t id,
					  Args &&... args); //Add a component of a specific type
	template <typename T>
	void DeleteComponentsById(
		std::uint32_t id); //Deletes all components of a specific type and id
	template <typename T>
	void DeleteComponents(); //Deletes all components of a specific type
	void DeleteAllComponentsOfId(
		std::uint32_t id); //Deletes all components of a specific id
	void DeleteAllComponents(); //Deletes all components

	template <typename T>
	std::vector<std::reference_wrapper<T>> GetComponentsByID(std::uint32_t id)
		const; //Get a vector<> of all components at specific type and id
	template <typename T>
	std::vector<std::reference_wrapper<T>> GetComponentsByType()
		const; //Get a vector<> of all components of a specific type

private:
	static ComponentManager mInstance; //Singleton

	ComponentManager(); //Singleton

	/*
	 * The std::unordered_map<std::type_index, std::vector<std::vector<std::unique_ptr<Component>>>> below might seem a bit strange, let me explain this structure:
	 * The std::unordered_map<> has a key and value. The key is a std::type_index and the value is a std::vector. So, a new std::vector will be created for each new std::type_index.
	 * The first std::vector<> stores another vector<>. This first vector<> is to bind the entity's id to a component.
	 * The second std::vector<> stores unique_ptrs. Each component can be gathered via an unique_ptr. This second vector<> allows multiple components of the same std::type_index for one entity (id).
	 */
	std::unordered_map<std::type_index,
					   std::vector<std::vector<std::unique_ptr<Component>>>>
		mComponents;
};

#include "ComponentManager.hpp"
