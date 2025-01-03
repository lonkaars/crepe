#pragma once

#include <format>

#include "ResourceManager.h"

namespace crepe {

template <typename T>
T & ResourceManager::get(const Asset & asset) {
	using namespace std;
	static_assert(
		is_base_of<Resource, T>::value, "cache must recieve a derivative class of Resource"
	);

	CacheEntry & entry = this->get_entry(asset);
	if (entry.resource == nullptr) entry.resource = make_unique<T>(asset, this->mediator);

	T * concrete_resource = dynamic_cast<T *>(entry.resource.get());
	if (concrete_resource == nullptr)
		throw runtime_error(format(
			"ResourceManager: mismatch between requested type and "
			"actual type of resource ({})",
			asset.get_path()
		));

	return *concrete_resource;
}

} // namespace crepe
