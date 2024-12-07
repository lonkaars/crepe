#pragma once

#include <type_traits>

#include "ComponentManager.h"
#include "types.h"

namespace crepe {

template <class T, typename... Args>
T & ComponentManager::add_component(game_object_id_t id, Args &&... args) {
	using namespace std;

	static_assert(is_base_of<Component, T>::value,
				  "add_component must recieve a derivative class of Component");

	// Determine the type of T (this is used as the key of the unordered_map<>)
	type_index type = typeid(T);

	// Check if this component type is already in the unordered_map<>
	if (this->components.find(type) == this->components.end()) {
		//If not, create a new (empty) vector<> of vector<unique_ptr<Component>>
		this->components[type] = vector<vector<unique_ptr<Component>>>();
	}

	// Resize the vector<> if the id is greater than the current size
	if (id >= this->components[type].size()) {
		// Initialize new slots to nullptr (resize does automatically init to nullptr)
		this->components[type].resize(id + 1);
	}

	// Create a new component of type T (arguments directly forwarded). The
	// constructor must be called by ComponentManager.
	T * instance_ptr = new T(id, forward<Args>(args)...);
	if (instance_ptr == nullptr) throw std::bad_alloc();

	T & instance_ref = *instance_ptr;
	unique_ptr<T> instance = unique_ptr<T>(instance_ptr);

	// Check if the vector size is not greater than get_instances_max
	int max_instances = instance->get_instances_max();
	if (max_instances != -1 && components[type][id].size() >= max_instances) {
		throw std::runtime_error(
			"Exceeded maximum number of instances for this component type");
	}

	// store its unique_ptr in the vector<>
	this->components[type][id].push_back(std::move(instance));

	return instance_ref;
}

template <typename T>
void ComponentManager::delete_components_by_id(game_object_id_t id) {
	using namespace std;

	// Do not delete persistent objects
	if (this->persistent[id]) {
		return;
	}

	// Determine the type of T (this is used as the key of the unordered_map<>)
	type_index type = typeid(T);

	// Find the type (in the unordered_map<>)
	if (this->components.find(type) != this->components.end()) {
		// Get the correct vector<>
		vector<vector<unique_ptr<Component>>> & component_array = this->components[type];

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

	if (this->components.find(type) == this->components.end()) return;

	// Loop through the whole vector<> of this specific type
	for (game_object_id_t i = 0; i < this->components[type].size(); ++i) {
		// Do not delete persistent objects
		if (!this->persistent[i]) {
			this->components[type][i].clear();
		}
	}
}

template <typename T>
RefVector<T> ComponentManager::get_components_by_id(game_object_id_t id) const {
	using namespace std;

	// Determine the type of T (this is used as the key of the unordered_map<>)
	type_index type = typeid(T);

	// Create an empty vector<>
	RefVector<T> component_vector;

	if (this->components.find(type) == this->components.end()) return component_vector;

	// Get the correct vector<>
	const vector<vector<unique_ptr<Component>>> & component_array = this->components.at(type);

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
RefVector<T> ComponentManager::get_components_by_type() const {
	using namespace std;

	// Determine the type of T (this is used as the key of the unordered_map<>)
	type_index type = typeid(T);

	// Create an empty vector<>
	RefVector<T> component_vector;

	// Find the type (in the unordered_map<>)
	if (this->components.find(type) == this->components.end()) return component_vector;

	// Get the correct vector<>
	const vector<vector<unique_ptr<Component>>> & component_array = this->components.at(type);

	// Loop through the whole vector<>
	for (const vector<unique_ptr<Component>> & component : component_array) {
		// Loop trough the whole vector<>
		for (const unique_ptr<Component> & component_ptr : component) {
			// Cast the unique_ptr to a raw pointer
			T * casted_component = static_cast<T *>(component_ptr.get());

			// Ensure that the cast was successful
			if (casted_component == nullptr) continue;

			// Add the dereferenced raw pointer to the vector<>
			component_vector.emplace_back(ref(*casted_component));
		}
	}

	// Return the vector<>
	return component_vector;
}

} // namespace crepe
