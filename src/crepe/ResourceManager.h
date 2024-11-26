#pragma once

#include <memory>
#include <unordered_map>

#include "api/Asset.h"

#include "Component.h"
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
	template <typename Resource>
	Resource & get_internal(const Component & component, const Asset & asset);

	template <typename Resource>
	const Asset & get_source(const Component & component) const;

	//! A cache that holds all the assets, accessible by their file path, over multiple scenes.
	std::unordered_map<const Asset, std::unique_ptr<Resource>> resources;

public:
	/**
	 * \brief Caches an asset by loading it from the given file path.
	 *
	 * \param file_path The path to the asset file to load.
	 * \param reload If true, the asset will be reloaded from the file, even if
	 * it is already cached.
	 * \tparam T The type of asset to cache (e.g., texture, sound, etc.).
	 * 
	 * \return A reference to the resource
	 * 
	 * This template function caches the asset at the given file path. If the
	 * asset is already cached, the existing instance will be returned.
	 * Otherwise, the concrete resource will be instantiated and added to the
	 * cache.
	 */
	template <typename Resource>
	void cache(const Asset & asset, bool persistent = false);

	template <typename Component>
	void cache(const Component & component, bool persistent = false);

	// void resman.cache<Resource>(Asset, Lifetime);
	// void resman.cache(Component, Asset, Lifetime);

	template <typename Resource, typename Component>
	Resource & get(const Component & component);

	//! Clear the resource cache
	void clear();
};

class Sound;
class AudioSource;
template <>
Sound & ResourceManager::get(const AudioSource & component);

} // namespace crepe

