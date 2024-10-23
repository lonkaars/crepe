#pragma once

#include <any>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace crepe::api {

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
								 bool reload = false) {
		auto it = asset_cache.find(file_path);

		if (!reload && it != asset_cache.end()) {
			return std::any_cast<std::shared_ptr<asset>>(it->second);
		}

		std::shared_ptr<asset> new_asset
			= std::make_shared<asset>(file_path.c_str());

		asset_cache[file_path] = new_asset;

		return new_asset;
	}
};

} // namespace crepe::api
