#pragma once

#include <stdexcept>
#include <format>

#include "ResourceManager.h"

namespace crepe {

template <typename T>
T & ResourceManager::cache(const Asset & asset) {
	using namespace std;
	static_assert(is_base_of<Resource, T>::value, "cache must recieve a derivative class of Resource");

	if (!this->resources.contains(asset))
		this->resources[asset] = make_unique<T>(asset);

	Resource * resource = this->resources.at(asset).get();
	T * concrete_resource = dynamic_cast<T *>(resource);

	if (concrete_resource == nullptr)
		throw runtime_error(format("ResourceManager: mismatch between requested type and actual type of resource ({})", asset.get_path()));

	return *concrete_resource;
}

} // namespace crepe
