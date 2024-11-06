#pragma once

#include <type_traits>

#include "ComponentManager.h"

namespace crepe {

template <class T, typename... Args>
T & ComponentManager::add_component(uint32_t id, Args &&... args) {
	using namespace std;

	static_assert(is_base_of<Component, T>::value,
				  "add_component must recieve a derivative class of Component");

	// Determine the type of T (this is used as the key of the unordered_map<>)
	type_index type = typeid(T);

	// Check if this component type is already in the unordered_map<>
	if (components.find(type) == components.end()) {
		//If not, create a new (empty) vector<> of vector<unique_ptr<Component>>
		components[type] = vector<vector<unique_ptr<Component>>>();
	}

	// Resize the vector<> if the id is greater than the current size
	if (id >= components[type].size()) {
		// Initialize new slots to nullptr (resize does automatically init to nullptr)
		components[type].resize(id + 1);
	}

	// Create a new component of type T (arguments directly forwarded). The
	// constructor must be called by ComponentManager.
	T * instance_pointer = new T(id, forward<Args>(args)...);
	unique_ptr<T> instance = unique_ptr<T>(instance_pointer);

	// Check if the vector size is not greater than get_instances_max
	if (instance->get_instances_max() != -1
		&& components[type][id].size() >= instance->get_instances_max()) {
		// TODO: Exception
		throw std::runtime_error(
			"Exceeded maximum number of instances for this component type");
	}

	// store its unique_ptr in the vector<>
	components[type][id].push_back(std::move(instance));

	return *instance;
}

template <typename T>
void ComponentManager::delete_components_by_id(uint32_t id) {
	using namespace std;

	// Determine the type of T (this is used as the key of the unordered_map<>)
	type_index type = typeid(T);

	// Find the type (in the unordered_map<>)
	if (components.find(type) != components.end()) {
		// Get the correct vector<>
		vector<vector<unique_ptr<Component>>> & component_array
			= components[type];

		// Make sure that the id (that we are looking for) is within the boundaries of the vector<>
		if (id < component_array.size()) {
			// Clear the whole vector<> of this specific type and id
			component_array[id].clear();
		}
	}
}

template <typename T>
void ComponentManager::delete_components() {
	// Determine the type of T (this is used as the key of the unordered_map<>)
	std::type_index type = typeid(T);

	if (components.find(type) == components.end()) return;

	components[type].clear();
}

template <typename T>
std::vector<std::reference_wrapper<T>>
ComponentManager::get_components_by_id(uint32_t id) const {
	using namespace std;

	// Determine the type of T (this is used as the key of the unordered_map<>)
	type_index type = typeid(T);

	// Create an empty vector<>
	vector<reference_wrapper<T>> component_vector;

	if (components.find(type) == components.end()) return component_vector;

	// Get the correct vector<>
	const vector<vector<unique_ptr<Component>>> & component_array
		= components.at(type);

	// Make sure that the id (that we are looking for) is within the boundaries of the vector<>
	if (id >= component_array.size()) return component_vector;

	// Loop trough the whole vector<>
	for (const unique_ptr<Component> & component_ptr : component_array[id]) {
		// Cast the unique_ptr to a raw pointer
		T * casted_component = static_cast<T *>(component_ptr.get());

		if (casted_component == nullptr) continue;

		// Add the dereferenced raw pointer to the vector<>
		component_vector.push_back(*casted_component);
	}

	return component_vector;
}

template <typename T>
std::vector<std::reference_wrapper<T>>
ComponentManager::get_components_by_type() const {
	using namespace std;

	// Determine the type of T (this is used as the key of the unordered_map<>)
	type_index type = typeid(T);

	// Create an empty vector<>
	vector<reference_wrapper<T>> component_vector;
	// Set the id to 0 (the id will also be stored in the returned vector<>)
	// uint32_t id = 0;

	// Find the type (in the unordered_map<>)
	if (components.find(type) == components.end()) return component_vector;

	// Get the correct vector<>
	const vector<vector<unique_ptr<Component>>> & component_array
		= components.at(type);

	// Loop through the whole vector<>
	for (const vector<unique_ptr<Component>> & component : component_array) {
		// Loop trough the whole vector<>
		for (const unique_ptr<Component> & component_ptr : component) {
			// Cast the unique_ptr to a raw pointer
			T * casted_component = static_cast<T *>(component_ptr.get());

			// Ensure that the cast was successful
			if (casted_component == nullptr) continue;

			// Pair the dereferenced raw pointer and the id and add it to the vector<>
			component_vector.emplace_back(ref(*casted_component));
		}

		// Increase the id (the id will also be stored in the returned vector<>)
		//++id;
	}

	// Return the vector<>
	return component_vector;
}

} // namespace crepe
