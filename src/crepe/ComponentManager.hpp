#pragma once

#include "ComponentManager.h"

namespace crepe {

template <typename T, typename... Args>
void ComponentManager::AddComponent(std::uint32_t id, Args &&... args) {
	// Determine the type of T (this is used as the key of the unordered_map<>)
	std::type_index type = typeid(T);

	// Check if this component type is already in the unordered_map<>
	if (components.find(type) == components.end()) {
		//If not, create a new (empty) vector<> of vector<unique_ptr<Component>>
		components[type] = std::vector<std::vector<std::unique_ptr<Component>>>();
	}

	// Resize the vector<> if the id is greater than the current size
	if (id >= components[type].size()) {
		// Initialize new slots to nullptr (resize does automatically init to nullptr)
		components[type].resize(id + 1);
	}

	// Create a new component of type T using perfect forwarding and store its
	// unique_ptr in the vector<>
	components[type][id].push_back(std::make_unique<T>(std::forward<Args>(args)...));
}

template <typename T>
void ComponentManager::DeleteComponentsById(std::uint32_t id) {
	// Determine the type of T (this is used as the key of the unordered_map<>)
	std::type_index type = typeid(T);

	// Find the type (in the unordered_map<>)
	if (components.find(type) != components.end()) {
		// Get the correct vector<>
		std::vector<std::vector<std::unique_ptr<Component>>> & componentArray = components[type];

		// Make sure that the id (that we are looking for) is within the boundaries of the vector<>
		if (id < componentArray.size()) {
			// Clear the whole vector<> of this specific type and id
			componentArray[id].clear();
		}
	}
}

template <typename T>
void ComponentManager::DeleteComponents() {
	// Determine the type of T (this is used as the key of the unordered_map<>)
	std::type_index type = typeid(T);

	// Find the type (in the unordered_map<>)
	if (components.find(type) != components.end()) {
		// Clear the whole vector<> of this specific type
		components[type].clear();
	}
}

template <typename T>
std::vector<std::reference_wrapper<T>>
ComponentManager::GetComponentsByID(std::uint32_t id) const {
	// Determine the type of T (this is used as the key of the unordered_map<>)
	std::type_index type = typeid(T);

	// Create an empty vector<>
	std::vector<std::reference_wrapper<T>> componentVector;

	// Find the type (in the unordered_map<>)
	if (components.find(type) != components.end()) {
		// Get the correct vector<>
		const std::vector<std::vector<std::unique_ptr<Component>>> & componentArray = components.at(type);

		// Make sure that the id (that we are looking for) is within the boundaries of the vector<>
		if (id < componentArray .size()) {
			// Loop trough the whole vector<>
			for (const std::unique_ptr<Component> & componentPtr : componentArray[id]) {
				// Cast the unique_ptr to a raw pointer
				T * castedComponent = static_cast<T *>(componentPtr.get());

				// Ensure that the cast was successful
				if (castedComponent) {
					// Add the dereferenced raw pointer to the vector<>
					componentVector.push_back(*castedComponent);
				}
			}
		}
	}

	// Return the vector<>
	return componentVector;
}

template <typename T>
std::vector<std::reference_wrapper<T>>
ComponentManager::GetComponentsByType() const {
	// Determine the type of T (this is used as the key of the unordered_map<>)
	std::type_index type = typeid(T);

	// Create an empty vector<>
	std::vector<std::reference_wrapper<T>> componentVector;
	// Set the id to 0 (the id will also be stored in the returned vector<>)
	// std::uint32_t id = 0;

	// Find the type (in the unordered_map<>)
	if (components.find(type) != components.end()) {

		// Get the correct vector<>
		const std::vector<std::vector<std::unique_ptr<Component>>> & componentArray = components.at(type);

		// Loop through the whole vector<>
		for (const std::vector<std::unique_ptr<Component>> & component : componentArray) {
			// Loop trough the whole vector<>
			for (const std::unique_ptr<Component> & componentPtr : component) {
				// Cast the unique_ptr to a raw pointer
				T * castedComponent = static_cast<T *>(componentPtr.get());

				// Ensure that the cast was successful
				if (castedComponent) {
					// Pair the dereferenced raw pointer and the id and add it to the vector<>
					componentVector.emplace_back(std::ref(*castedComponent));
				}
			}

			// Increase the id (the id will also be stored in the returned vector<>)
			//++id;
		}
	}

	// Return the vector<>
	return componentVector;
}

}

