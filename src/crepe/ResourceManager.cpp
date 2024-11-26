#include <stdexcept>

#include "util/Log.h"

#include "ResourceManager.h"

using namespace crepe;
using namespace std;

ResourceManager::~ResourceManager() { dbg_trace(); }
ResourceManager::ResourceManager() { dbg_trace(); }

void ResourceManager::clear() {
	this->resources.clear();
}

// template <typename T>
// T & ResourceManager::cache(const Asset & asset) {
// 	dbg_trace();
// 	static_assert(is_base_of<Resource, T>::value, "cache must recieve a derivative class of Resource");
// 
// 	if (!this->resources.contains(asset))
// 		this->resources[asset] = make_unique<T>(asset);
// 
// 	Resource * resource = this->resources.at(asset).get();
// 	T * concrete_resource = dynamic_cast<T *>(resource);
// 
// 	if (concrete_resource == nullptr)
// 		throw runtime_error(format("ResourceManager: mismatch between requested type and actual type of resource ({})", asset.get_path()));
// 
// 	return *concrete_resource;
// }
// 
// #include "facade/Sound.h"
// template Sound & ResourceManager::cache(const Asset &);

