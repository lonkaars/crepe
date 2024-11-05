#pragma once

#include <any>
#include <memory>
#include <string>
#include <unordered_map>

namespace crepe {

class AssetManager {

private:
	std::unordered_map<std::string, std::any> asset_cache;

private:
	AssetManager();
	virtual ~AssetManager();

public:
	AssetManager(const AssetManager &) = delete;
	AssetManager(AssetManager &&) = delete;
	AssetManager & operator=(const AssetManager &) = delete;
	AssetManager & operator=(AssetManager &&) = delete;

	static AssetManager & get_instance();

public:
	template <typename asset>
	std::shared_ptr<asset> cache(const std::string & file_path,
								 bool reload = false);
};

} // namespace crepe

#include "AssetManager.hpp"
