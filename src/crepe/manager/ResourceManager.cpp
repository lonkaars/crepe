#include "util/dbg.h"

#include "ResourceManager.h"

using namespace crepe;
using namespace std;

ResourceManager::ResourceManager(Mediator & mediator) : Manager(mediator) {
	dbg_trace();
	mediator.resource_manager = *this;
}
ResourceManager::~ResourceManager() { dbg_trace(); }

void ResourceManager::clear() {
	std::erase_if(this->resources, [](const pair<const Asset, CacheEntry> & pair) {
		const CacheEntry & entry = pair.second;
		return entry.persistent == false;
	});
}

void ResourceManager::clear_all() { this->resources.clear(); }

void ResourceManager::set_persistent(const Asset & asset, bool persistent) {
	this->get_entry(asset).persistent = persistent;
}

ResourceManager::CacheEntry & ResourceManager::get_entry(const Asset & asset) {
	if (!this->resources.contains(asset)) this->resources[asset] = {};
	return this->resources.at(asset);
}
