#pragma once

#include <any>
#include <memory>
#include <string>
#include <unordered_map>

namespace crepe {

/**
 * \brief The AssetManager is responsible for storing and managing assets over multiple scenes.
 *
 * The AssetManager ensures that assets are loaded once and can be accessed across different
 * scenes. It caches assets to avoid reloading them every time a scene is loaded. Assets are
 * retained in memory until the AssetManager is destroyed, at which point the cached assets are
 * cleared.
 */
class AssetManager {

private:
	//! A cache that holds all the assets, accessible by their file path, over multiple scenes.
	std::unordered_map<std::string, std::any> asset_cache;

private:
	AssetManager();
	virtual ~AssetManager();

public:
	AssetManager(const AssetManager &) = delete;
	AssetManager(AssetManager &&) = delete;
	AssetManager & operator=(const AssetManager &) = delete;
	AssetManager & operator=(AssetManager &&) = delete;

	/**
	 * \brief Retrieves the singleton instance of the AssetManager.
	 *
	 * \return A reference to the single instance of the AssetManager.
	 */
	static AssetManager & get_instance();

public:
	/**
	 * \brief Caches an asset by loading it from the given file path.
	 *
	 * \param file_path The path to the asset file to load.
	 * \param reload If true, the asset will be reloaded from the file, even if it is already
	 * cached.
	 * \tparam T The type of asset to cache (e.g., texture, sound, etc.).
	 *
	 * \return A shared pointer to the cached asset.
	 *
	 * This template function caches the asset at the given file path. If the asset is already
	 * cached and `reload` is false, the existing cached version will be returned. Otherwise, the
	 * asset will be reloaded and added to the cache.
	 */
	template <typename T>
	std::shared_ptr<T> cache(const std::string & file_path, bool reload = false);
};

} // namespace crepe

#include "AssetManager.hpp"
