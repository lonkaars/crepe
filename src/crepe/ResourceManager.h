#pragma once

#include <memory>
#include <unordered_map>

#include "api/Asset.h"

#include "Resource.h"

namespace crepe {

/**
 * \brief The ResourceManager is responsible for storing and managing assets over
 * multiple scenes.
 * 
 * The ResourceManager ensures that assets are loaded once and can be accessed
 * across different scenes. It caches assets to avoid reloading them every time
 * a scene is loaded. Assets are retained in memory until the ResourceManager is
 * destroyed, at which point the cached assets are cleared.
 */
class ResourceManager {
public:
	ResourceManager(); // dbg_trace
	virtual ~ResourceManager(); // dbg_trace

private:
	struct CacheEntry {
		std::unique_ptr<Resource> resource = nullptr;
		bool persistent = false;
	};
	//! A cache that holds all the assets, accessible by their file path, over multiple scenes.
	std::unordered_map<const Asset, CacheEntry> resources;
	CacheEntry & get_entry(const Asset & asset);

public:
	void set_persistent(const Asset & asset, bool persistent);

	template <typename Resource>
	Resource & get(const Asset & asset);

	void clear();
	void clear_all();
};

} // namespace crepe

#include "ResourceManager.hpp"
