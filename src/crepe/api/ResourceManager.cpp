#include "util/Log.h"

#include "ResourceManager.h"

// default resource cache functions
#include "../facade/Sound.h"

using namespace crepe;

ResourceManager & ResourceManager::get_instance() {
	static ResourceManager instance;
	return instance;
}

ResourceManager::~ResourceManager() { dbg_trace(); }
ResourceManager::ResourceManager() { dbg_trace(); }

void ResourceManager::clear() {
	this->resources.clear();
}

template <>
Sound & ResourceManager::cache<Sound>(const Asset & asset) {
	return this->cache<Sound>(asset);
}

