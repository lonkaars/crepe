#pragma once

#include <memory>
#include <unordered_map>

#include "Asset.h"
#include "Resource.h"

namespace crepe {

class Sound;

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

private:
	//! A cache that holds all the assets, accessible by their file path, over multiple scenes.
	std::unordered_map<const Asset, std::unique_ptr<Resource>> resources;

private:
	ResourceManager(); // dbg_trace
	virtual ~ResourceManager(); // dbg_trace

	ResourceManager(const ResourceManager &) = delete;
	ResourceManager(ResourceManager &&) = delete;
	ResourceManager & operator=(const ResourceManager &) = delete;
	ResourceManager & operator=(ResourceManager &&) = delete;

public:
	/**
	 * \brief Retrieves the singleton instance of the ResourceManager.
	 *
	 * \return A reference to the single instance of the ResourceManager.
	 */
	static ResourceManager & get_instance();

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
	template <typename T>
	T & cache(const Asset & asset);

	//! Clear the resource cache
	void clear();
};

} // namespace crepe

