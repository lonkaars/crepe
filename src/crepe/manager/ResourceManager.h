#pragma once

#include <memory>
#include <unordered_map>

#include "../Resource.h"
#include "../api/Asset.h"

#include "Manager.h"

namespace crepe {

/**
 * \brief Owner of concrete Resource instances
 * 
 * ResourceManager caches concrete Resource instances per Asset. Concrete resources are
 * destroyed at the end of scenes by default, unless the game programmer marks them as
 * persistent.
 */
class ResourceManager : public Manager {
public:
	ResourceManager(Mediator & mediator);
	virtual ~ResourceManager(); // dbg_trace

private:
	//! Cache entry
	struct CacheEntry {
		//! Concrete resource instance
		std::unique_ptr<Resource> resource = nullptr;
		//! Prevent ResourceManager::clear from removing this entry
		bool persistent = false;
	};
	//! Internal cache
	std::unordered_map<const Asset, CacheEntry> resources;
	/**
	 * \brief Ensure a cache entry exists for this asset and return a mutable reference to it
	 *
	 * \param asset Asset the concrete resource is instantiated from
	 *
	 * \returns Mutable reference to cache entry
	 */
	CacheEntry & get_entry(const Asset & asset);

public:
	/**
	 * \brief Mark a resource as persistent (i.e. used across multiple scenes)
	 *
	 * \param asset Asset the concrete resource is instantiated from
	 * \param persistent Whether this resource is persistent (true=keep, false=destroy)
	 */
	void set_persistent(const Asset & asset, bool persistent);

	/**
	 * \brief Retrieve reference to concrete Resource by Asset
	 *
	 * \param asset Asset the concrete resource is instantiated from
	 * \tparam Resource Concrete derivative of Resource
	 *
	 * This class instantiates the concrete resource if it is not yet stored in the internal
	 * cache, or returns a reference to the cached resource if it already exists.
	 *
	 * \returns Reference to concrete resource
	 *
	 * \throws std::runtime_error if the \c Resource parameter does not match with the actual
	 * type of the resource stored in the cache for this Asset
	 */
	template <typename Resource>
	Resource & get(const Asset & asset);

	//! Clear non-persistent resources from cache
	void clear();
	//! Clear all resources from cache regardless of persistence
	void clear_all();
};

} // namespace crepe

#include "ResourceManager.hpp"
