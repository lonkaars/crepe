

#include "AssetManager.h"
#include "util/log.h"

using namespace crepe::api;

AssetManager & AssetManager::get_instance() {
	static AssetManager instance;
	return instance;
}

AssetManager::~AssetManager() {
	dbg_trace();
	this->asset_cache.clear();
}

AssetManager::AssetManager() { dbg_trace(); }
