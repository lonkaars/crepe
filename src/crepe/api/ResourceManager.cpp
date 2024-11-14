#include "util/Log.h"

#include "ResourceManager.h"

using namespace crepe;

ResourceManager & ResourceManager::get_instance() {
	static ResourceManager instance;
	return instance;
}

ResourceManager::~ResourceManager() {
	dbg_trace();
	this->asset_cache.clear();
}

ResourceManager::ResourceManager() { dbg_trace(); }
